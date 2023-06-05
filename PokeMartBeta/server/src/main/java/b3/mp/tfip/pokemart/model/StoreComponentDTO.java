package b3.mp.tfip.pokemart.model;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
public class StoreComponentDTO {

    private String productID;
    private String productName;
    private double cost;
    private int quantity;
    private double discount;
    private double deduct;

}
