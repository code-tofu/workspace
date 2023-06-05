package b3.mp.tfip.pokemart.service;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.dao.DataAccessException;
import org.springframework.stereotype.Service;

import b3.mp.tfip.pokemart.model.StoreComponentDTO;
import b3.mp.tfip.pokemart.repository.InventoryRepo;

@Service
public class InventoryService {

    @Autowired
    InventoryRepo invRepo;

    public List<StoreComponentDTO> getStoreComponentData(int limit, int offset) throws DataAccessException {
        return invRepo.getStoreComponentData(limit, offset);
    }
}