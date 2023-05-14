package com.in28m.firstwebapp.todo;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.function.Predicate;

import org.springframework.stereotype.Service;

import jakarta.validation.Valid;

@Service
public class TodoService {


    private static List<Todo> todos = new ArrayList<>();
    private static int todosCount = 3;

    //creating a static block to mock up the todolist
    static {
        todos.add(new Todo(1, "in28minutes","Get AWS Certification", LocalDate.now().plusYears(1), false ));
        todos.add(new Todo(2, "in28minutes","Learn DevOps", LocalDate.now().plusYears(2), false ));
        todos.add(new Todo(3, "in28minutes","Learn Full Stack Development", LocalDate.now().plusYears(3), false ));
    }

    public List<Todo> findByUsername(String username){
        Predicate<? super Todo> predicate = todo -> todo.getUsername().equalsIgnoreCase(username);
        return todos.stream().filter(predicate).toList();
    }

    public void addTodo(String username, String description, LocalDate targetDate, boolean done) {
		Todo todo = new Todo(++todosCount,username,description,targetDate,done);
		todos.add(todo);
	}
	
    public void deleteById(int id) {
		//todo.getId() == id
		// todo -> todo.getId() == id
		Predicate<? super Todo> predicate = todo -> todo.getId() == id;
		todos.removeIf(predicate);
	}

	public Todo findById(int id) {
		Predicate<? super Todo> predicate = todo -> todo.getId() == id;
		Todo todo = todos.stream().filter(predicate).findFirst().get();
		return todo;
	}

    public void updateTodo(@Valid Todo todo){
        deleteById(todo.getId());
        todos.add(todo);
    }
    // it is a replacement, but because array list is sorted it will be added to the bottom of the list
    
}


