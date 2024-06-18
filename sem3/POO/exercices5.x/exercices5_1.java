//realiser avec Thibault Chatillon
import java.util.*;

class exercices5_1{

    private Map<String, String> props;

    public exercices5_1(){
        this.props = new HashMap<String, String>();
    }

    public String getProperty(String key) {
    /* TODO */
        return this.props.get(key);
    }
    public String getPropertyOrElse(String key, String defaultValue) {
    /* TODO */
        return this.props.getOrDefault(key, defaultValue);
    }
    public void addProperty(String key, String value) {
    /* TODO */
        this.props.put(key, value);
    }
    public List<String> keys() {
    /* TODO */
        return new ArrayList<>(this.props.keySet());
    }
    public List<String> values() {
        return new ArrayList<>(this.props.values());
    /* TODO */
    }
    public Map<String, String> allProperties() {
    /* TODO */
        return this.props;
    }
}