<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="start.aspx.cs" Inherits="zad4.start" %>


<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Deklaracje</title>
</head>
<body>
    <form id="form1" runat="server">
        <div>
            Imię:
            <asp:TextBox runat="server" ID="NameField"></asp:TextBox><br />
            Nazwisko:
            <asp:TextBox runat="server" ID="SurnameField"></asp:TextBox><br />
            Data:
            <asp:TextBox runat="server" ID="DateField"></asp:TextBox><br />
            Zajęcia:
            <asp:TextBox runat="server" ID="SubjectField"></asp:TextBox><br />
            Nr zestawu:
            <asp:TextBox runat="server" ID="NoField"></asp:TextBox><br />
            Pkt za zad 1
            <asp:TextBox runat="server" ID="z1Box" onkeydown = "return !(event.keyCode>=65);"></asp:TextBox><br />
            Pkt za zad 2
            <asp:TextBox runat="server" ID="z2Box" onkeydown = "return !(event.keyCode>=65);"></asp:TextBox><br />
            Pkt za zad 3
            <asp:TextBox runat="server" ID="z3Box" onkeydown = "return !(event.keyCode>=65);"></asp:TextBox><br />
            Pkt za zad 4
            <asp:TextBox runat="server" ID="z4Box" onkeydown = "return !(event.keyCode>=65);"></asp:TextBox><br />
            Pkt za zad 5
            <asp:TextBox runat="server" ID="z5Box" onkeydown = "return !(event.keyCode>=65);"></asp:TextBox><br />
            Pkt za zad 6
            <asp:TextBox runat="server" ID="z6Box" onkeydown = "return !(event.keyCode>=65);"></asp:TextBox><br />
            Pkt za zad 7 
            <asp:TextBox runat="server" ID="z7Box" onkeydown = "return !(event.keyCode>=65);"></asp:TextBox><br />
            Pkt za zad 8
            <asp:TextBox runat="server" ID="z8Box" onkeydown = "return !(event.keyCode>=65);"></asp:TextBox><br />
            Pkt za zad 9
            <asp:TextBox runat="server" ID="z9Box" onkeydown = "return !(event.keyCode>=65);"></asp:TextBox><br />
            Pkt za zad 10
            <asp:TextBox runat="server" ID="z10Box" onkeydown = "return !(event.keyCode>=65);"></asp:TextBox><br />
            <asp:Button runat="server" Text="Wyślij" ID="submitButton" /><br />
        </div>
    </form>
</body>
</html>
