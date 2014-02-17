using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Xml;

namespace UIForSpecialist
{
    public partial class Index : System.Web.UI.Page
    {
        string accountXmlPath = HttpContext.Current.ApplicationInstance.Server.MapPath("~/App_Data/")+"accountData.xml";
        string loginRole = "";
        XmlNode node;
        bool admit = false;
        protected void Page_Load(object sender, EventArgs e)
        {
        }
        
        protected void loginBtn_Click(object sender, EventArgs e)
        {
            
            XmlDocument xmlDoc = load_xml(accountXmlPath);
            runningThrough(xmlDoc.DocumentElement);
            if (admit == true)
            {
                Response.Redirect("/About.aspx");
            }
            else
            {
                Response.Write("<script type='text/javascript'>alert('We don't konw you yet, why not register firs:)');</script>");
            }
        }

        private XmlDocument load_xml(string filepath){
            XmlDocument xmlDoc = new XmlDocument();
            xmlDoc.Load(filepath);

            return xmlDoc;
        }

        protected void runningThrough(XmlNode nod)
        {
            node = nod;

            if (node.HasChildNodes == false && node.Attributes != null)
            {
                if (node.Attributes["username"].Value == this.Request["username"] &&
                    node.Attributes["code"].Value == this.Request["code"])
                {
                    loginRole = node.Attributes["role"].Value;
                    admit = true;
                    Session["role"] = node.Attributes["role"].Value;
                    Session["username"] = node.Attributes["username"].Value;
                    Session["email"] = node.Attributes["email"].Value;
                }
            }
            else
            {
                foreach (XmlNode child in node.ChildNodes)
                    runningThrough(child);
            }
        }
    }
}