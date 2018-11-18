using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Canvas
{
    static class Controller
    {
        private static MainPage mainPage = new MainPage();
        private static Stack<UserControl> controlStack = new Stack<UserControl>();

        public static void Start()
        {
            Push(new LoginControl());
            mainPage.UserPanelVisible(false);
            mainPage.Show();
            if (!File.Exists(Database.dbFile))
            {
                var loginControl = controlStack.First() as LoginControl;        
                loginControl.StartLoading();
                new Task(() =>
                {
                    Database.Create();
                    loginControl.StopLoading();
                }).Start();
            }
            Application.Run();
        }

        public static void Exit()
        {
            Application.Exit();
        }

        private static void Push(UserControl userControl)
        {
            controlStack.Push(userControl);
            mainPage.SetPanel(userControl);
            mainPage.UserPanelVisible(controlStack.Count > 1);
        }

        private static void Pop()
        {
            controlStack.Pop();
            if (controlStack.Count == 0)
            {
                Application.Exit();
            }
            else 
            {
                mainPage.SetPanel(controlStack.First());
            }
            if (controlStack.Count == 1)
            {
                mainPage.UserPanelVisible(false);
            }
        }

        public static bool TryLogin(string userID)
        {
            var result = Database.GetUser(userID);
            if (result is User)
            {
                mainPage.SetUserName(result.ToString());
                Push(new AdminControl());
                return true;
            }
            else
            {
                return false;
            }
        }

        public static void Logout()
        {
            while (controlStack.Count > 1)
            {
                Pop();
            }
        }
    }
}
