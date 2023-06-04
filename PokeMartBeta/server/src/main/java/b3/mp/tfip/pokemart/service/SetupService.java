package b3.mp.tfip.pokemart.service;

import java.util.Optional;
import java.util.Random;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.dao.DataAccessException;
import org.springframework.http.RequestEntity;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;
import org.springframework.web.client.HttpClientErrorException;
import org.springframework.web.client.RestTemplate;
import org.springframework.web.util.UriComponentsBuilder;

import b3.mp.tfip.pokemart.repository.ProductRepo;
import b3.mp.tfip.pokemart.utils.ProductUtils;
import b3.mp.tfip.pokemart.utils.Utils;
import jakarta.json.JsonObject;

@Service
public class SetupService {

    public static final int MAX_ITEM_ID = 999;

    @Value("${api.poke.data.uri}")
    private String pokeAPI;

    @Autowired
    ProductRepo productRepo;

    public void createNewDatabase(int size) {
        Random rand = new Random();
        for (int i = 0; i < size;) {
            try {
                System.out.println(">>Creating Product #" + (i + 1));
                int randInt = rand.nextInt(MAX_ITEM_ID) + 1;
                Optional<String> itemJsonStr = getProductDataFromAPI(randInt);

                if (itemJsonStr.isEmpty()) {
                    System.out.println(">>Empty Response. Restarting Download");
                    continue;
                }

                JsonObject productJson = Utils.getJsonObjectFromStr(itemJsonStr.get());
                if (!productRepo.insertProduct(ProductUtils.createProductDAOFromJson(productJson))) {
                    System.out.println(">>Insertion into DB Failed. Restarting Download");
                    continue;
                }

                i += 1;
                Thread.sleep(1000); // rate limiter

            } catch (InterruptedException interErr) {
                System.out.println(">>Downloading Interrupted. Restarting Download");
            } catch (DataAccessException daErr) {
                System.out.println(daErr);
                System.out.println(">>DataAccessException. Restarting Download");
                break;
            }

        }
        System.out.println(">>Created New Database of Size:" + size);
    }

    public Optional<String> getProductDataFromAPI(int productID) {
        String itemURL = UriComponentsBuilder.fromUriString(pokeAPI).pathSegment("item")
                .pathSegment(Integer.toString(productID)).toUriString();
        System.out.println(">>Retrieve Product Data from:" + itemURL);
        RestTemplate restTemplate = new RestTemplate();
        RequestEntity<Void> req = RequestEntity.get(itemURL).build();

        try {
            ResponseEntity<String> resp = restTemplate.exchange(req, String.class);
            System.out.println("--out-resp:" + resp.getBody());
            return Optional.of(resp.getBody());
        } catch (HttpClientErrorException httpErr) {
            System.out.println(">>PokeAPI Server Error:" + httpErr);
            return Optional.empty();
        }
    }

}
