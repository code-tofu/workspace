package b3.mp.tfip.pokemart.controller;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.dao.DataAccessException;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;

import b3.mp.tfip.pokemart.model.StoreComponentDTO;
import b3.mp.tfip.pokemart.service.InventoryService;
import jakarta.json.Json;
import jakarta.json.JsonObject;

@RestController
public class InventoryController {

    @Autowired
    InventoryService invSvc;

    @GetMapping("/inventory/storeMain")
    public ResponseEntity<String> getStoreMainData(@RequestParam(defaultValue = "10") String limit,
            @RequestParam(defaultValue = "0") String offset) {
        try {
            List<StoreComponentDTO> storeCompList = invSvc.getStoreComponentData(Integer.parseInt(limit),
                    Integer.parseInt(offset));
            ObjectMapper mapper = new ObjectMapper();
            return ResponseEntity.status(HttpStatus.OK).body(mapper.writeValueAsString(storeCompList));
        } catch (NumberFormatException nfErr) {
            System.err.println(">> [ERROR] " + nfErr);
            JsonObject resp = Json.createObjectBuilder()
                    .add("400 Error", "Request Params limit and/or offset needs to be a integer").build();
            return ResponseEntity.status(HttpStatus.BAD_REQUEST).body(resp.toString());
        } catch (DataAccessException daErr) {
            System.err.println(">> [ERROR] " + daErr);
            JsonObject resp = Json.createObjectBuilder().add("500 Internal Server Error", "Request Failed")
                    .build();
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).body(resp.toString());
        } catch (JsonProcessingException jsErr) {
            System.err.println(">> [ERROR] " + jsErr);
            JsonObject resp = Json.createObjectBuilder().add("500 Internal Server Error", "Request Failed")
                    .build();
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).body(resp.toString());
        }
    }
}