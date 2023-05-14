package paf.rev.pokemart.util;

import java.io.StringReader;

import jakarta.json.Json;
import jakarta.json.JsonObject;
import jakarta.json.JsonReader;


public class JsonUtil {
    
    public static JsonObject JsonStr2Obj(String jsonString){
        StringReader sr = new StringReader(jsonString.toString());
        JsonReader jsr = Json.createReader(sr);
        return (JsonObject)jsr.read();
        }
    


}
