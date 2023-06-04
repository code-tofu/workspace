package b3.mp.tfip.pokemart.utils;

import b3.mp.tfip.pokemart.model.ProductDAO;
import jakarta.json.JsonArray;
import jakarta.json.JsonObject;
import jakarta.json.JsonValue;

import static b3.mp.tfip.pokemart.model.ProductDAO.SPRITE_URL_ROOT;

public class ProductUtils {

    public static ProductDAO createProductDAOFromJson(JsonObject pokeJsonObj) {
        String details = getENflavourText(pokeJsonObj.getJsonArray("flavor_text_entries")) + " " +
                pokeJsonObj.getJsonArray("effect_entries").getJsonObject(0).getString("effect");
        ProductDAO newProduct = new ProductDAO(
                Utils.generateUUID(8),
                pokeJsonObj.getInt("id"),
                pokeJsonObj.getString("name"),
                pokeJsonObj.getJsonObject("category").getString("name"),
                pokeJsonObj.getJsonNumber("cost").doubleValue(),
                details,
                getENname(pokeJsonObj.getJsonArray("names")),
                removeURLroot(pokeJsonObj.getJsonObject("sprites").getString("default")),
                null);
        return newProduct;
    }

    private static String getENflavourText(JsonArray pokeJsonArr) {
        for (JsonValue pokeJsonObj : pokeJsonArr) {
            String lang = pokeJsonObj.asJsonObject().getJsonObject("language").getString("name");
            if (lang.equals("en")) {
                return pokeJsonObj.asJsonObject().getString("text")
                        .replace("\n", " ")
                        .replace("’", "'");
            }
        }
        return "";
    }

    private static String getENname(JsonArray pokeJsonArr) {
        for (JsonValue pokeJsonObj : pokeJsonArr) {
            String lang = pokeJsonObj.asJsonObject().getJsonObject("language").getString("name");
            if (lang.equals("en")) {
                return pokeJsonObj.asJsonObject().getString("name");
            }
        }
        return "";
    }

    private static String removeURLroot(String url) {
        return url.replace(SPRITE_URL_ROOT, "");
    }

}
