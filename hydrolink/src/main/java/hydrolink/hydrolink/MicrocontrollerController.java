package hydrolink.hydrolink;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/api")
public class MicrocontrollerController {

    @Autowired
    private MicrocontrollerService service;

    @GetMapping("/led")
    public String controlLed(@RequestParam String state) {
        return service.sendCommand(state);
    }
}
