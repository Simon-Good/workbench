<%@ Page Language="C#" MasterPageFile="~/Front.master" AutoEventWireup="true" CodeBehind="Index.aspx.cs" Inherits="UIForSpecialist.Index" %>

<asp:Content ID="HeaderContent" runat="server" ContentPlaceHolderID="HeadContent">
 
</asp:Content>
<asp:Content ID="BodyContent" runat="server" ContentPlaceHolderID="MainContent">

<form id="Form1" runat="server">
<div class="container">
    <div class="row">
        <div class="col-md-6 col-md-offset-3 panel panel-default">
            <form class="margin-base-vertical">
            <br />
            <br />
                <p class="input-group">
                    <span class="input-group-addon"><span class="glyphicon glyphicon-user"></span></span>
                    <input type="text" class="form-control input-lg" name="username" placeholder="username" />
                </p>
                <p class="input-group">
                    <span class="input-group-addon"><span class="glyphicon glyphicon-credit-card"></span></span>
                    <input type="text" class="form-control input-lg" name="code" placeholder="code"/>
                </p>
                <p class="text-center">
                    <asp:Button runat="server" ID="loginBtn" Text="登录" CssClass="btn btn-success btn-lg" onclick="loginBtn_Click" />
                </p>
            </form>

        </div><!-- //main content -->
    </div><!-- //row -->
</div> <!-- //container -->
</form>
</asp:Content>