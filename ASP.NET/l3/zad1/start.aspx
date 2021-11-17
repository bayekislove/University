<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="start.aspx.cs" Inherits="zadanie1.start" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Zadanie 1 - start</title>
</head>
<body>
    <div>
        <form id="f1" runat="server">
            <input type="text" value="asda" />
            <input type="submit" value="Form that GETs" onclick="return getFunc()"/>
        </form>
    </div>
    <div>
        <a href="a.html" onclick="document.getElementById('f1').submit()">Href that POSTs</a>
    </div>
    <script>
        function getFunc(event) {
            location.href = '/a.html';
        }
    </script>
</body>
</html>
