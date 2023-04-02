<!DOCTYPE html>
<html lang="en">
<head>
        <!-- CSS link for webjars bootstrap -->
        <link href="webjars/bootstrap/5.1.3/css/bootstrap.min.css" rel="stylesheet" >

    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Welcome to the Login Page!</title>
</head>
<body>

    <div class="container">
    <!-- Jasper seems to ignore this if it does not exist in the model? -->
    <p>${errorMessage}</p>

    
    <form method="post">
        Name: <input type="text" name="name">
        Password: <input type="password" name="password">
        <input type="submit">
    </form>
    </div>

<!-- JS link for webjars bootstrap -->
<script src="webjars/bootstrap/5.1.3/js/bootstrap.min.js"></script>
<script src="webjars/jquery/3.6.0/jquery.min.js"></script>
</body>
</html>