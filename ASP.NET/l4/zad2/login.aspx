<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="login.aspx.cs" Inherits="zad2.login" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
        Formularz logowania<br />
        login:<asp:TextBox id="loginBox" runat="server"></asp:TextBox><br />
        haslo:<asp:TextBox id="passwodBox" TextMode="Password" runat="server"></asp:TextBox><br />
        <asp:Button id="submit" runat="server" OnClick="submit_Click" Text="Login"/><br />
        <asp:Label id="resultLabel" runat="server"></asp:Label>
        <asp:Button id="redirectToRegister" runat="server" OnClick="redirectToRegister_Click" Text="Register"/>
    </form>
</body>
</html>
