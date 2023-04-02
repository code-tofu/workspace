<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<!-- using jsp fragments for common elements -->
<%@ include file="common/header.jspf" %>
<%@ include file="common/navigation.jspf" %>	

<!DOCTYPE html>
<html lang="en">
<head>
    <!-- CSS link for webjars bootstrap -->
    <link href="webjars/bootstrap/5.1.3/css/bootstrap.min.css" rel="stylesheet" >

    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>To Do List</title>
</head>
<body>

    <!-- bootstrap includes all content into container -->
    <!-- <div class="container">
        <h1>Your Todos</h1>
        <table class="table">
            <thead>
                <tr>
                    <th>id</th>
                    <th>Description</th>
                    <th>Target Date</th>
                    <th>Is Done?</th>
                </tr>
            </thead>
            <tbody>		
                <c:forEach items="${todos}" var="todo">
                    <tr>
                        <td>${todo.id}</td>
                        <td>${todo.description}</td>
                        <td>${todo.targetDate}</td>
                        <td>${todo.done}</td>
                        <td> <a href="delete-todo?id=${todo.id}" class="btn btn-warning">Delete</a>   </td>
                        <td> <a href="update-todo?id=${todo.id}" class="btn btn-success">Update</a>   </td>
                    </tr>
                </c:forEach>
            </tbody>
        </table>
        </div>
        <a href="add-todo" class="btn btn-success">Add Todo</a> -->
        <!-- Using query param to tell the endponit which id todo to delete -->
    

    <div class="container">
        <h1>Your Todos</h1>
        <table class="table">
            <thead>
                <tr>
                    <th>Username</th>
                    <th>Description</th>
                    <th>Target Date</th>
                    <th>Is Done?</th>
                    <th></th>
                    <th></th>
                </tr>
            </thead>
            <tbody>		
                <c:forEach items="${todos}" var="todo">
                    <tr>
                        <td>${todo.username}</td>
                        <td>${todo.description}</td>
                        <td>${todo.targetDate}</td>
                        <td>${todo.done}</td>
                        <td> <a href="delete-todo?id=${todo.id}" class="btn btn-warning">Delete</a>   </td>
                        <td> <a href="update-todo?id=${todo.id}" class="btn btn-success">Update</a>   </td>
                    </tr>
                </c:forEach>
            </tbody>
        </table>
        <a href="add-todo" class="btn btn-success">Add Todo</a>
    </div>
    <%@ include file="common/footer.jspf" %>


<!-- JS link for webjars bootstrap -->
<script src="webjars/bootstrap/5.1.3/js/bootstrap.min.js"></script>
<script src="webjars/jquery/3.6.0/jquery.min.js"></script>
</body>
</html>