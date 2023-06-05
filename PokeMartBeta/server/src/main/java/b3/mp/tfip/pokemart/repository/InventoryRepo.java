package b3.mp.tfip.pokemart.repository;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.dao.DataAccessException;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Repository;

import b3.mp.tfip.pokemart.model.StoreComponentDTO;

import static b3.mp.tfip.pokemart.repository.InventoryQueries.*;

import java.util.List;

@Repository
public class InventoryRepo {

    @Autowired
    JdbcTemplate jTemplate;

    public boolean insertInventoryItem(String productID, int quantity) throws DataAccessException {
        try {
            jTemplate.update(INSERT_NEW_INVENTORY_ITEM, productID, quantity);
            return true;
        } catch (DataAccessException daErr) {
            System.out.println(">> [ERROR] " + daErr);
            System.out.println(">> [WARNING] Insert Inventory: Existing Stock Already Exists");
            return false;
        }
    }

    public List<StoreComponentDTO> getStoreComponentData(int limit, int offset) throws DataAccessException {
        return jTemplate.query(SELECT_STOREITEMCOMPONENT_DATA_LIMITED, new StoreComponentMapper(), limit, offset);
    }

}
