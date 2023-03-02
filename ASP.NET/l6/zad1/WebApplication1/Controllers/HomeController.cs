using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using WebApplication1.Models;

namespace WebApplication1.Controllers
{
    public class HomeController : Controller
    {
        public ActionResult Index(
            int page = 1,
            string sort = "GivenName", string sortdir = "ASC")
        {
            var model = new WebGridDemoIndexModel();
            var dataLayer = new DataLayer();

            model.Users = new PagedEnumerable<User>()
            {
                Items = dataLayer.GetUsers(string.Format("{0} {1}", sort, sortdir), (page - 1) * 10, 10),
                TotalCount = dataLayer.TotalUsers()
            };

            return View(model);
        }

        public ActionResult Add()
        {
            return Redirect("/Add");
        }
    }
}