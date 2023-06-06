package b3.mp.tfip.pokemart.controller;

import java.util.List;
import java.util.Map;
import java.util.Optional;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.dao.DataAccessException;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;

import b3.mp.tfip.pokemart.model.CatalogueComponentDTO;
import b3.mp.tfip.pokemart.service.InventoryService;
import jakarta.json.Json;
import jakarta.json.JsonArrayBuilder;
import jakarta.json.JsonObject;
import jakarta.json.JsonObjectBuilder;

@RestController
public class InventoryController {

    @Autowired
    InventoryService invSvc;

    @GetMapping("api/inventory/storeMain")
    public ResponseEntity<String> getStoreMain(@RequestParam(defaultValue = "10") String limit,
            @RequestParam(defaultValue = "0") String offset) {
        try {
            List<CatalogueComponentDTO> storeCompList = invSvc.getStoreComponentData(Integer.parseInt(limit),
                    Integer.parseInt(offset));
            ObjectMapper mapper = new ObjectMapper();
            return ResponseEntity.status(HttpStatus.OK).body(mapper.writeValueAsString(storeCompList));
        } catch (Exception ex) {
            return ExceptionHandler(ex);
        }
    }

    @GetMapping("api/inventory/categoryMain")
    public ResponseEntity<String> getAllInventoryCategories() {
        try {
            Map<String, Integer> categoryMap = invSvc.getAllInventoryCategories();
            JsonArrayBuilder jsonAB = Json.createArrayBuilder();
            JsonObjectBuilder jsonOB = Json.createObjectBuilder();
            for (Map.Entry<String, Integer> entry : categoryMap.entrySet()) {
                jsonAB.add(jsonOB.add("category", entry.getKey()).add("count", entry.getValue()));
            }
            return ResponseEntity.status(HttpStatus.OK).body(jsonAB.build().toString());
        } catch (Exception ex) {
            return ExceptionHandler(ex);
        }
    }

    @GetMapping("api/inventory/category/{category}")
    public ResponseEntity<String> getInventoryByCategory(@PathVariable String category) {
        try {
            List<CatalogueComponentDTO> storeCompListCategory = invSvc.getStoreComponentDataByCategory(category);
            ObjectMapper mapper = new ObjectMapper();
            return ResponseEntity.status(HttpStatus.OK).body(mapper.writeValueAsString(storeCompListCategory));
        } catch (Exception ex) {
            return ExceptionHandler(ex);
        }
    }

    @GetMapping("api/inventory/{productID}")
    public ResponseEntity<String> getStockofProduct(@PathVariable String productID) {
        try {
            Optional<Integer> quantity = invSvc.getStockofProduct(productID);
            if (quantity.isEmpty())
                throw new Exception("ProductID not in inventory");
            JsonObjectBuilder jsonOB = Json.createObjectBuilder().add("productID", productID).add("quantity",
                    quantity.get());
            return ResponseEntity.status(HttpStatus.OK).body(jsonOB.build().toString());
        } catch (Exception ex) {
            return ExceptionHandler(ex);
        }
    }

    public ResponseEntity<String> ExceptionHandler(Exception ex) {
        if (ex instanceof NumberFormatException) {
            System.err.println(">> [ERROR] " + ex);
            JsonObject resp = Json.createObjectBuilder()
                    .add("400 Error", "Request Params limit and/or offset needs to be a integer").build();
            return ResponseEntity.status(HttpStatus.BAD_REQUEST).body(resp.toString());
        }
        if (ex instanceof DataAccessException) {
            System.err.println(">> [ERROR] " + ex);
            JsonObject resp = Json.createObjectBuilder().add("500 Internal Server Error", "Request Failed")
                    .build();
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).body(resp.toString());
        }
        if (ex instanceof JsonProcessingException) {
            System.err.println(">> [ERROR] " + ex);
            JsonObject resp = Json.createObjectBuilder().add("500 Internal Server Error", "Request Failed")
                    .build();
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).body(resp.toString());
        }
        JsonObjectBuilder jsonOB = Json.createObjectBuilder().add("Error", ex.toString());
        return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).body(jsonOB.build().toString());
    }
}
