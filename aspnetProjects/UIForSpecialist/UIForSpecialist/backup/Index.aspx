<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Index.aspx.cs" Inherits="UIForSpecialist.Index1" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<asp:Content ID="HeaderContent" runat="server" ContentPlaceHolderID="HeadContent">
 <style>

        /* http://css-tricks.com/perfect-full-page-background-image/ */
        html {
            background: url(img/Aerial_view_-_Shasta_Dam_CA.jpg) no-repeat center center fixed; 
            -webkit-background-size: cover;
            -moz-background-size: cover;
            -o-background-size: cover;
            background-size: cover;
        }

        body {
            padding-top: 20px;
            font-size: 16px;
            font-family: "Open Sans",serif;
            background: transparent;
        }

        h1 {
            font-family: "Abel", Arial, sans-serif;
            font-weight: 400;
            font-size: 40px;
        }

        /* Override B3 .panel adding a subtly transparent background */
        .panel {
            background-color: rgba(255, 255, 255, 0.9);
        }

        .margin-base-vertical {
            margin: 40px 0;
        }

    </style>
</asp:Content>
<asp:Content ID="BodyContent" runat="server" ContentPlaceHolderID="MainContent">
<body>
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
                        <asp:Button runat="server" ID="loginBtn" Text="登录" CommandName="getLoginRequest" CssClass="btn btn-success btn-lg" />
                    </p>
                </form>

            </div><!-- //main content -->
        </div><!-- //row -->
    </div> <!-- //container -->
    </form>
</body>
</html>
</asp:Content>
