package com.in28m.firstwebapp.todo;

import java.time.LocalDate;
import java.util.List;

import org.springframework.security.core.Authentication;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.stereotype.Controller;
import org.springframework.ui.ModelMap;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.SessionAttributes;

import jakarta.validation.Valid;

@Controller
@SessionAttributes("name")
public class TodoController {

    
    public TodoController(TodoService todoService) {
		super();
		this.todoService = todoService;
	}

	private TodoService todoService;
		
	
	@RequestMapping("list-todos")
	public String listAllTodos(ModelMap model) {
		String username = (String)model.get("name");
		List<Todo> todos = todoService.findByUsername(getLoggedinUsername(model)); //solutionhere?
		model.addAttribute("todos", todos);
		return "listTodos";
	}


	// @RequestMapping(value="add-todo", method = RequestMethod.GET)
	// public String showNewTodoPage() {
	// 	return "todo";
	// }


	// @RequestMapping(value="add-todo", method = RequestMethod.POST)
	// public String addNewTodo(@RequestParam String description, ModelMap model) {
	// 	String username = (String)model.get("name");
	// 	// adding logic should be performed by the service.
	// 	todoService.addTodo(username, description, LocalDate.now().plusYears(1), false);
	// 	return "redirect:list-todos";
	// 	// redirecting instead of having to add all the models again
	// }

	@RequestMapping(value="add-todo", method = RequestMethod.GET)
	public String showNewTodoPage(ModelMap model) {
		//adding the model to have the form backing bean. "name" is from the session
		String username = (String)model.get("name");
		Todo todo = new Todo(0, username, "Default Desc", LocalDate.now().plusYears(1), false);
		model.put("todo", todo);
		return "todo";
	}

	@RequestMapping(value="add-todo", method = RequestMethod.POST)
	public String addNewTodo(ModelMap model,@Valid Todo todo,BindingResult result) {
		if(result.hasErrors()) {
			return "todo";
		}

		String username = (String)model.get("name"); //STILL NULL?
		todoService.addTodo(username, todo.getDescription(), todo.getTargetDate(), false);
		System.out.println(todo);
		
		return "redirect:list-todos";
	}

	@RequestMapping(value="update-todo", method = RequestMethod.GET)
	public String showUpdateTodoPage(@RequestParam int id, ModelMap model) {
		Todo todo = todoService.findById(id);
		model.addAttribute("todo", todo);
		return "todo";
	}

	@RequestMapping(value="update-todo", method = RequestMethod.POST)
	public String updateTodo(ModelMap model, @Valid Todo todo, BindingResult result) {
		
		if(result.hasErrors()) {
			return "todo";
		}
		
		String username = (String)model.get("name");
		todo.setUsername(username);
		todoService.updateTodo(todo);
		return "redirect:list-todos";
	}

	private String getLoggedinUsername(ModelMap model) { //remove modelmap model?
        Authentication authentication = 
                SecurityContextHolder.getContext().getAuthentication();
        return authentication.getName();
    }

}
