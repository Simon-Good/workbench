using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace UIForSpecialist
{
    public partial class SiteMaster : System.Web.UI.MasterPage
    {
        protected string username = "";
        protected string role = "";
        protected void Page_Load(object sender, EventArgs e)
        {
            if (Session["username"] != null)
            {
                username = Session["username"].ToString();
            }
            if (Session["role"] != null)
            {
                role = Session["role"].ToString();
            }
        }

        protected void logOutBtn_Click(object sender, EventArgs e)
        {
            Session.Abandon();
            Session.Clear();
            Response.Redirect("/Index.aspx");
        }

        protected void treeSchMnBtn_Click(object sender, EventArgs e)
        {
            if (role.Equals("admin"))
            {
                Response.Redirect("/TreeSearch-admin.aspx");
            }
            else if (role.Equals("user"))
            {
                Response.Redirect("/TreeSearch-user.aspx");
            }
            else
            {
                Response.Write("<script type='text/javascript'>alert('帐号问题，请尝试重新登录或联系管理员！');</script>");
            }
        }

        protected void caseSchMnBtn_Click(object sender, EventArgs e)
        {
            if (role.Equals("admin"))
            {
                Response.Redirect("/CaseSearch-admin.aspx");
            }
            else if (role.Equals("user"))
            {
                Response.Redirect("/CaseSearch-user.aspx");
            }
            else
            {
                Response.Write("<script type='text/javascript'>alert('帐号问题，请尝试重新登录或联系管理员！');</script>");
            }
        }

        protected void factorDdMnBtn_Click(object sender, EventArgs e)
        {
            if (role.Equals("admin"))
            {
                Response.Redirect("/CaseSearch-admin.aspx");
            }
            else if (role.Equals("user"))
            {
                Response.Redirect("/CaseSearch-user.aspx");
            }
            else
            {
                Response.Write("<script type='text/javascript'>alert('帐号问题，请尝试重新登录或联系管理员！');</script>");
            }
        }
    }
}
