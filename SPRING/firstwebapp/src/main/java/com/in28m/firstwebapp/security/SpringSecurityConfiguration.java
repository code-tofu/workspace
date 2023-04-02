package com.in28m.firstwebapp.security;

import java.util.function.Function;


import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.security.core.userdetails.User;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.security.provisioning.InMemoryUserDetailsManager;

@Configuration
public class SpringSecurityConfiguration {
	//LDAP or Database
	//In Memory 
	
	//InMemoryUserDetailsManager
	//InMemoryUserDetailsManager(UserDetails... users)
	
	@Bean
	public InMemoryUserDetailsManager createUserDetailsManager() {
		
		UserDetails userDetails1 = createNewUser("in28minutes", "dummy");
		UserDetails userDetails2 = createNewUser("ranga", "dummydummy");
		
        //accepts var args
		return new InMemoryUserDetailsManager(userDetails1, userDetails2);
	}

	private UserDetails createNewUser(String username, String password) {
		Function<String, String> passwordEncoder
		= input -> passwordEncoder().encode(input);

		UserDetails userDetails = User.builder()
									.passwordEncoder(passwordEncoder)
									.username(username)
									.password(password)
									.roles("USER","ADMIN")
									.build();
		return userDetails;
	}

	@Bean
	public PasswordEncoder passwordEncoder() {
		return new BCryptPasswordEncoder();
	}
	
}


// @Configuration
// public class SpringSecurityConfiguration {

//     // Usually uses a database, in this case we use in memory

//     //InMemoryUserDetailsManager
// 	//InMemoryUserDetailsManager(UserDetails... users)
	
//     // @Bean
// 	// public InMemoryUserDetailsManager createUserDetailsManager() {
// 	// 	UserDetails userDetails = User.withDefaultPasswordEncoder()
// 	// 	.username("in28minutes")
// 	// 	.password("dummy")
// 	// 	.roles("USER","ADMIN")
// 	// 	.build()
// 	// 	return new InMemoryUserDetailsManager(userDetails);
// 	// }

// 	//Spring auto replacees default password encoder with Bcrypt encoder when specified
// 	//use password encoder and configure it when the function

// 	@Bean
// 	public InMemoryUserDetailsManager createUserDetailsManager() {
		
// 		Function<String, String> passwordEncoder
// 				= input -> passwordEncoder().encode(input);
		
// 		UserDetails userDetails = User.builder()
// 									.passwordEncoder(passwordEncoder)
// 									.username("in28minutes")
// 									.password("dummy")
// 									.roles("USER","ADMIN")
// 									.build();
		
// 		return new InMemoryUserDetailsManager(userDetails);
// 	}

// 	@Bean
// 	public PasswordEncoder passwordEncoder() {
// 		return new BCryptPasswordEncoder();
// 	}
    
// }
