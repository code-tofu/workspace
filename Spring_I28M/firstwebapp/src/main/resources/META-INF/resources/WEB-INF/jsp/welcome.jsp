<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Welcome</title>
</head>
<body>
    <%@ include file="common/header.jspf" %>
    <%@ include file="common/navigation.jspf" %>	
    <div class="container">
        <h1>Welcome ${name}</h1>
        <a href="list-todos">Manage</a> your todos
    </div>
    <%@ include file="common/footer.jspf" %>
</body>
</html>