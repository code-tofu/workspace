package b3.mp.tfip.pokemart.model;

import java.util.Arrays;

public class ProductDAO {

    public static final String SPRITE_URL_ROOT = "https://raw.githubusercontent.com/PokeAPI/sprites/master/sprites/items/";

    private String productID;
    private int apiID;
    private String nameID;
    private String category;
    private double cost;
    private String details;
    private String productName;
    private String spritesURL;
    private byte[] sprite;

    public String getProductID() {
        return productID;
    }

    public void setProductID(String productID) {
        this.productID = productID;
    }

    public int getApiID() {
        return apiID;
    }

    public void setApiID(int apiID) {
        this.apiID = apiID;
    }

    public String getNameID() {
        return nameID;
    }

    public void setNameID(String nameID) {
        this.nameID = nameID;
    }

    public String getCategory() {
        return category;
    }

    public void setCategory(String category) {
        this.category = category;
    }

    public double getCost() {
        return cost;
    }

    public void setCost(double cost) {
        this.cost = cost;
    }

    public String getDetails() {
        return details;
    }

    public void setDetails(String details) {
        this.details = details;
    }

    public String getProductName() {
        return productName;
    }

    public void setProductName(String productName) {
        this.productName = productName;
    }

    public String getSpritesURL() {
        return spritesURL;
    }

    public void setSpritesURL(String spritesURL) {
        this.spritesURL = spritesURL;
    }

    public byte[] getSprite() {
        return sprite;
    }

    public void setSprite(byte[] sprite) {
        this.sprite = sprite;
    }

    public ProductDAO() {
    }

    public ProductDAO(String productID, int apiID, String nameID, String category, double cost, String details,
            String productName, String spritesURL, byte[] sprite) {
        this.productID = productID;
        this.apiID = apiID;
        this.nameID = nameID;
        this.category = category;
        this.cost = cost;
        this.details = details;
        this.productName = productName;
        this.spritesURL = spritesURL;
        this.sprite = sprite;
    }

    @Override
    public String toString() {
        return "ProductDAO [productID=" + productID + ", apiID=" + apiID + ", nameID=" + nameID + ", category="
                + category + ", cost=" + cost + ", details=" + details + ", productName=" + productName
                + ", spritesURL=" + spritesURL + ", sprite=" + Arrays.toString(sprite) + "]";
    }

}
