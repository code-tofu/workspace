package b3.mp.tfip.pokemart.repository;

import java.sql.ResultSet;
import java.sql.SQLException;

import org.springframework.jdbc.core.RowMapper;

import b3.mp.tfip.pokemart.model.StoreComponentDTO;

public class StoreComponentMapper implements RowMapper<StoreComponentDTO> {

    @Override
    public StoreComponentDTO mapRow(ResultSet rs, int rowNum) throws SQLException {
        return new StoreComponentDTO(
                rs.getString("product_id"),
                rs.getString("product_name"),
                rs.getDouble("cost"),
                rs.getInt("quantity"),
                rs.getDouble("discount"),
                rs.getDouble("deduct"));
    }
}
