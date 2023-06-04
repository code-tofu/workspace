package b3.mp.tfip.pokemart.repository;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.dao.DataAccessException;
import org.springframework.dao.EmptyResultDataAccessException;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Repository;

import b3.mp.tfip.pokemart.model.ProductDAO;

import static b3.mp.tfip.pokemart.repository.ProductQueries.*;

import java.util.Optional;

@Repository
public class ProductRepo {

    @Autowired
    JdbcTemplate jTemplate;

    public boolean insertProduct(ProductDAO newProd) throws DataAccessException {
        try {
            Optional<ProductDAO> existingProd = getProductByApiID(newProd.getApiID());
            if (existingProd.isPresent())
                System.out.println(">>Insert Product: Product Already Exists");
            return false;
        } catch (EmptyResultDataAccessException emptyResultErr) {
            jTemplate.update(INSERT_NEW_PRODUCT,
                    newProd.getProductID(),
                    newProd.getApiID(),
                    newProd.getNameID(),
                    newProd.getCategory(),
                    newProd.getCost(),
                    newProd.getDetails(),
                    newProd.getProductName(),
                    newProd.getSpritesURL(),
                    null);
            return true;
        }
    }

    public Optional<ProductDAO> getProductByApiID(int apiID) throws DataAccessException {
        return Optional.of(jTemplate.queryForObject(SELECT_PRODUCT_BY_API_ID, new ProductMapper(), apiID));
    }

    public Optional<ProductDAO> getProductByProductID(String productID) throws DataAccessException {
        return Optional.of(jTemplate.queryForObject(SELECT_PRODUCT_BY_PRODUCT_ID, new ProductMapper(), productID));
    }

}
