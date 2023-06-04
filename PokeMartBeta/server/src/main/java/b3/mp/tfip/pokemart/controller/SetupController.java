package b3.mp.tfip.pokemart.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import b3.mp.tfip.pokemart.service.SetupService;
import jakarta.json.Json;
import jakarta.json.JsonObject;

@RestController
public class SetupController {

    public static final String PRODUCT_DB_DEFAULT_SIZE = "10";

    @Autowired
    SetupService setupSvc;

    @GetMapping("/api/setup/createProductDB")
    public ResponseEntity<String> createProductDB(@RequestParam(defaultValue = PRODUCT_DB_DEFAULT_SIZE) String size) {
        try {
            setupSvc.createNewDatabase(Integer.parseInt(size));
            JsonObject resp = Json.createObjectBuilder().add("Created Database", size).build();
            return ResponseEntity.status(HttpStatus.CREATED).body(resp.toString());

        } catch (NumberFormatException NFerr) {
            System.err.println(">> [ERROR] " + NFerr);
            JsonObject resp = Json.createObjectBuilder().add("400 Error", "Query Params 'size' needs to be a integer")
                    .build();
            return ResponseEntity.status(HttpStatus.BAD_REQUEST).body(resp.toString());
        }
    }

}
