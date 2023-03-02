<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="register.aspx.cs" Inherits="zad2.register" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
        Formularz rejestracji<br />
        email:<asp:TextBox id="emailBox" runat="server"></asp:TextBox><br />
        login:<asp:TextBox id="loginBox" runat="server"></asp:TextBox><br />
        haslo:<asp:TextBox id="passwodBox" TextMode="Password" runat="server"></asp:TextBox><br />
        <asp:Button id="submit" runat="server" OnClick="submit_Click" Text="Register"/>
    </form>
</body>
</html>
