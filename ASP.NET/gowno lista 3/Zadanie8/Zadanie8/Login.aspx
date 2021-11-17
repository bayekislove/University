<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Login.aspx.cs" Inherits="Zadanie8.Login" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
        <div>
            <asp:TextBox ID="login" runat="server"></asp:TextBox>
            <asp:TextBox ID="haslo" TextMode="Password" runat="server"></asp:TextBox>
            <asp:Button ID="bt" runat="server" Text="Loguj" onServerClick="OnMove" OnClientClick="OnMove" />
        </div>
    </form>
</body>
</html>
