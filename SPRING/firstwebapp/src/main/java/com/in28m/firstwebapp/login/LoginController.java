package com.in28m.firstwebapp.login;

import org.springframework.stereotype.Controller;
import org.springframework.ui.ModelMap;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.SessionAttributes;

@Controller
@SessionAttributes("name")
public class LoginController {

    // @RequestMapping("login")
	// public String gotoLoginPage() {
	// 	return "login";
	// }

    // //http://localhost:8080/login?name=BruceWayne
    // @RequestMapping("login")
	// public String gotoLoginPage(@RequestParam String name, ModelMap model) {
	// 	model.put("name", name);
	// 	System.out.println("Request param is " + name); //NOT RECOMMENDED FOR PROD CODE
	// 	return "login";
	// }

    
    // @RequestMapping("login")
	// public String gotoLoginPage() {
	// 	return "login";
	// }
    
    // @RequestMapping(value="login", method=RequestMethod.GET)
	// public String gotoLoginPage() {
	// 	return "login";
	// }

    // //note that in this case, the method signature is different
    // @RequestMapping(value="login", method=RequestMethod.POST)
	// public String gotoLoginPage(@RequestParam String name, @RequestParam String password, ModelMap model) {
    //     model.put("name",name);
    //     model.put("password",password);
	// 	return "welcome";
	// }

    //if it is not initialised, then it will be null.
  
    private AuthenticationService authenticationService;
	
    //using constructor injection
    //need to make authetication service a springbeen
	public LoginController(AuthenticationService authenticationService) {
		super();
		this.authenticationService = authenticationService;
	}

	@RequestMapping(value="login",method = RequestMethod.GET)
	public String gotoLoginPage() {
		return "login";
	}

	@RequestMapping(value="login",method = RequestMethod.POST)
	//login?name=Ranga RequestParam
	public String gotoWelcomePage(@RequestParam String name, 
			@RequestParam String password, ModelMap model) {
		
		if(authenticationService.authenticate(name, password)) {
			model.put("name", name);
			//Authentication 
			//name - in28minutes
			//password - dummy
			
			return "welcome";
		}
		
        model.put("errorMessage","Invalid Credentials Please try again");
		return "login";
	}


}

