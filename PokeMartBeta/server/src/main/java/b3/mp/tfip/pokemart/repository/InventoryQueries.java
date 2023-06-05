package b3.mp.tfip.pokemart.repository;

public class InventoryQueries {

    public static final String INSERT_NEW_INVENTORY_ITEM = "INSERT INTO inventory (product_id,quantity) VALUES (?,?)";

    public static final String SELECT_STOREITEMCOMPONENT_DATA_LIMITED = """
            SELECT product_data.product_id,product_data.product_name,product_data.cost, inventory.quantity, inventory.discount, inventory.deduct
            FROM product_data
            JOIN inventory ON product_data.product_id = inventory.product_id
            WHERE inventory.quantity>0
            LIMIT ? OFFSET ?;
                """;

}
