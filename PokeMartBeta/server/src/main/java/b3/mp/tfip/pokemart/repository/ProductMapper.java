package b3.mp.tfip.pokemart.repository;

import java.sql.ResultSet;
import java.sql.SQLException;

import org.springframework.jdbc.core.RowMapper;

import b3.mp.tfip.pokemart.model.ProductDAO;

public class ProductMapper implements RowMapper<ProductDAO> {

    @Override
    public ProductDAO mapRow(ResultSet rs, int rowNum) throws SQLException {
        ProductDAO product = new ProductDAO(
                rs.getString("product_id"),
                rs.getInt("api_id"),
                rs.getString("name_id"),
                rs.getString("category"),
                rs.getDouble("cost"),
                rs.getString("details"),
                rs.getString("product_name"),
                rs.getString("spritesURL"),
                null);
        // rs.getBytes("sprite")
        return product;
    }
}

// public ProductDAO(String productID, int apiID, String nameID, String
// category, double cost, String details, String productName, String spritesURL,
// byte[] sprite)
// +--------------+--------------+------+-----+---------+-------+
// | Field | Type | Null | Key | Default | Extra |
// +--------------+--------------+------+-----+---------+-------+
// | product_id | varchar(10) | NO | | NULL | |
// | api_id | int | NO | | NULL | |
// | name_id | varchar(50) | NO | | NULL | |
// | category | varchar(50) | YES | | NULL | |
// | cost | double(8,2) | NO | | NULL | |
// | details | varchar(500) | NO | | NULL | |
// | product_name | varchar(50) | NO | | NULL | |
// | spritesURL | varchar(255) | YES | | NULL | |
// | sprite | mediumblob | YES | | NULL | |
// +--------------+--------------+------+-----+---------+-------+