package hydrolink.hydrolink;

//import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;
//import org.springframework.web.client.RestTemplate;

@Service
public class MicrocontrollerService {

    public String sendCommand(String state) {
        return "Command sent: " + state;
    }
}
