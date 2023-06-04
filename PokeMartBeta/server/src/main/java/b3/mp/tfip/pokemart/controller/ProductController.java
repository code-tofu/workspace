package b3.mp.tfip.pokemart.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;

import b3.mp.tfip.pokemart.service.ProductService;
import jakarta.json.Json;
import jakarta.json.JsonObject;

@Controller
public class ProductController {

    @Autowired
    ProductService productSvc;

    @GetMapping("/api/product/{id}")
    public ResponseEntity<String> getProductByProductID(@PathVariable String id) {
        // teststring
        // handlenotfound
        System.out.println(productSvc.getProductByProductID(id).get());
        return ResponseEntity.ok().build();
    }

    @GetMapping("/api/setup/product/{id}")
    public ResponseEntity<String> getProductByApiID(@PathVariable String id) {
        // teststring
        // handlenotfound
        try {
            System.out.println(productSvc.getProductByApiID(Integer.parseInt(id)).get());
            return ResponseEntity.ok().build();

        } catch (NumberFormatException NFerr) {
            System.err.println(">>Error:" + NFerr);
            JsonObject resp = Json.createObjectBuilder()
                    .add("400 Error", "Path Variable <id> needs to be a integer").build();
            return ResponseEntity.status(HttpStatus.BAD_REQUEST).body(resp.toString());
        }
    }

}
