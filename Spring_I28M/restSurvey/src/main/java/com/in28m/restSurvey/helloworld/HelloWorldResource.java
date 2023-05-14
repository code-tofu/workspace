package com.in28m.restSurvey.helloworld;

import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.RestController;

//@Controller
@RestController
public class HelloWorldResource {
	
	@RequestMapping("/hello-world")
    // @ResponseBody
    // @RestController returns response body instead of the view
	public String helloWorld() {
		return "Hello World";
	}
	
    // bean is auto converted into a json by Jackson included in springboot starter web
	@RequestMapping("/hello-world-bean")
	public HelloWorldBean helloWorldBean() {
		return new HelloWorldBean("Hello World");
	}
	//Path Variable or Path Params
	// /user/Ranga/todos/1

	@RequestMapping("/hello-world-path-param/{name}")
	public HelloWorldBean helloWorldPathParam(@PathVariable String name) {
		return new HelloWorldBean("Hello " + name + "!");
	}
	
	@RequestMapping("/hello-world-path-param/{name}/message/{message}")
	public HelloWorldBean helloWorldMultiplePathParam
					(@PathVariable String name,
							@PathVariable String message) {
		return new HelloWorldBean("Hello World " + name + "," + message);
	}

}