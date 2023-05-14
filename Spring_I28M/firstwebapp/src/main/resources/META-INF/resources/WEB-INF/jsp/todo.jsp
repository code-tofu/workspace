<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib prefix="form" uri="http://www.springframework.org/tags/form" %>
<%@ include file="common/header.jspf" %>
<%@ include file="common/navigation.jspf" %>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link href="webjars/bootstrap/5.1.3/css/bootstrap.min.css" rel="stylesheet" >
    <link href="webjars/bootstrap-datepicker/1.9.0/css/bootstrap-datepicker.standalone.min.css" rel="stylesheet" >
    <title>Add Todo Page</title>	
</head>
<body>
    <!-- <div class="container">
        <h1>Enter Todo Details</h1> -->

        <!-- front end validated, but can be easily overwritten. require server side validation -->
        <!-- <form method="post">
            Description: <input type="text" name="description" required="required"/>
        </form> -->
        <!-- prefix:form (in this case, form:form). form:input maps to the path of the member variable of the modelAttribute -->
        <!-- Hidden variables are included so that these variables are not empty/null when "todo" bean is initalised -->
			<!-- <form:form method="post" modelAttribute="todo"> -->

            <!-- fieldset is a html tag to wrap fields together -->
            <!-- mb3 is bootstrap's marging class selector -->
            <!-- <fieldset class="mb-3">				
                <form:label path="description">Description</form:label>
                <form:input type="text" path="description" required="required"/>
                <form:errors path="description" cssClass="text-warning"/>
            </fieldset>
            <fieldset class="mb-3">				
                <form:label path="targetDate">Target Date</form:label>
                <form:input type="text" path="targetDate" required="required"/>
                <form:errors path="targetDate" cssClass="text-warning"/>
            </fieldset>

				<form:input type="hidden" path="id"/>
				<form:input type="hidden" path="done"/>
                <input type="submit" class="btn btn-success"/>
			</form:form> -->
        <!-- spring tag usses cssClass instead of class? -->

    <!-- </div> -->

    <div class="container">
	
        <h1>Enter Todo Details</h1>
        
        <form:form method="post" modelAttribute="todo">
            <fieldset class="mb-3">				
                <form:label path="description">Description</form:label>
                <form:input type="text" path="description" required="required"/>
                <form:errors path="description" cssClass="text-warning"/>
            </fieldset>
            <fieldset class="mb-3">				
                <form:label path="targetDate">Target Date</form:label>
                <form:input type="text" path="targetDate" required="required"/>
                <form:errors path="targetDate" cssClass="text-warning"/>
            </fieldset>
            <form:input type="hidden" path="id"/>
            <form:input type="hidden" path="done"/>
            <input type="submit" class="btn btn-success"/>
        
        </form:form>
        
    </div>
    <%@ include file="common/footer.jspf" %>


    <script src="webjars/bootstrap/5.1.3/js/bootstrap.min.js"></script>
    <script src="webjars/jquery/3.6.0/jquery.min.js"></script>
    <script src="webjars/bootstrap-datepicker/1.9.0/js/bootstrap-datepicker.min.js"></script>

    <!-- id of field should be in the parentheses, use #as ID picker -->
    <script type="text/javascript">
        $('#targetDate').datepicker({
            format: 'yyyy-mm-dd'
        });
    </script>
</body>
</html>