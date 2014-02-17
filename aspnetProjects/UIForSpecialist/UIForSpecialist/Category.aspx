<%@ Page Title="" Language="C#" MasterPageFile="~/Front.Master" AutoEventWireup="true" CodeBehind="Category.aspx.cs" Inherits="UIForSpecialist.Category" %>
<asp:Content ID="Content1" ContentPlaceHolderID="HeadContent" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
<form id="Form1" runat="server">
<div class="container">
    <div class="row">
            <div class="col-md-6 col-md-offset-3 panel panel-default btn-group btn-group-vertical">
            <br />
                  <form class="margin-base-vertical">
                        <asp:Button runat="server" ID="treeSchBtn" Text="目录故障检索" 
                            CssClass="btn btn-success btn-lg" onclick="treeSchBtn_Click"/><br />
                        <asp:Button runat="server" ID="caseSchBtn" Text="案例故障查询" 
                            CssClass="btn btn-success btn-lg" onclick="caseSchBtn_Click"/>  <br />
                        <asp:Button runat="server" ID="factorRfrBtn" Text="条件故障诊断" 
                            CssClass="btn btn-success btn-lg" onclick="factorRfrBtn_Click"/>  <br />
                        <asp:Button runat="server" ID="aboutBtn" Text="关于本系统" 
                            CssClass="btn btn-success btn-lg" onclick="aboutBtn_Click"/><br />
                  </form>
            </div>
            <br />
    </div><!-- //row -->
</div> <!-- //container -->
</form>
</asp:Content>
