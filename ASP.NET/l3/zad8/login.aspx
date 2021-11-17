<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="login.aspx.cs" Inherits="zad8.login" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
        <asp:Label runat="server" ID="result"></asp:Label><br />
        <asp:Label runat="server">login</asp:Label>
        <asp:TextBox ID="lgn" runat="server"></asp:TextBox><br />
        <asp:Label runat="server">haslo</asp:Label>
        <asp:TextBox ID="pwd" TextMode="Password" runat="server"></asp:TextBox><br />
        <asp:Button ID="send" runat="server" Text="aaa" onClick="Validate" />
    </form>
</body>
</html>
