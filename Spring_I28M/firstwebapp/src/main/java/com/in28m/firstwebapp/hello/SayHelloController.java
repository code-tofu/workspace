package com.in28m.firstwebapp.hello;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller
//annotations tell spring that this is a spring bean
public class SayHelloController {
    
    // http://localhost:8080/say-hello
	@RequestMapping("say-hello")
	//mapping the URL to the method
	@ResponseBody
	public String sayHello() {
		return "Hello! What are you learning today?";
		//spring is looking for a view if it is just a pure pring
        //Responsebody tells the browser to display the spring instead of looking for a view
	}

	// http://localhost:8080/say-hello-html
	@RequestMapping("say-hello-html")
	@ResponseBody
	public String sayHelloHtml() {
        //using a stringbuffer to return a html string
		StringBuffer sb = new StringBuffer();
		sb.append("<html>");
		sb.append("<head>");
		sb.append("<title> My First HTML Page - Changed</title>");
		sb.append("</head>");
		sb.append("<body>");
		sb.append("My first html page with body - html stringbuffer");
		sb.append("</body>");
		sb.append("</html>");
		
		return sb.toString();
	}

	// http://localhost:8080/say-hello-jsp
	// This is the default folder that spring uses to store the view templates
    // /src/main/resources/META-INF/resources/WEB-INF/jsp/sayHello.jsp
	@RequestMapping("say-hello-jsp")
	public String sayHelloJsp() {
		return "sayHello";
	}


}
