using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SQLite;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Canvas
{
    static class Database
    {
        public static readonly string dbFile = "db.sqlite";
        private static readonly string nameFile = @"..\..\names.txt";

        public static void Create()
        {
            SQLiteConnection.CreateFile(dbFile);
            using (var conn = new SQLiteConnection(@"Data Source=" + dbFile))
            {
                conn.Open();
                using (var cmd = new SQLiteCommand(conn))
                {
                    cmd.CommandType = CommandType.Text;
                    cmd.CommandText =
                        @"CREATE TABLE Users (UserID INTEGER PRIMARY KEY, " +
                        @"FirstName TEXT NOT NULL, LastName TEXT NOT NULL);";
                    cmd.Prepare();
                    cmd.ExecuteNonQuery();
                }
                conn.Close();
            }          
            if (File.Exists(nameFile))
            {
                foreach (string line in File.ReadAllLines(nameFile))
                {
                    var name = line.Split();
                    if (name.Length == 2)
                    {
                        CreateUser(name[0], name[1]);
                    }
                }
            }
            else
            {
                throw new FileNotFoundException(nameFile);
            }
        }

        public static List<User> GetUsers(string filter = null)
        {
            List<User> list = new List<User>();
            using (var conn = new SQLiteConnection(@"Data Source=" + dbFile))
            {
                conn.Open();
                using (var cmd = conn.CreateCommand())
                {
                    cmd.CommandType = CommandType.Text;
                    cmd.CommandText = @"SELECT * FROM Users";
                    cmd.Prepare();
                    using (var res = cmd.ExecuteReader())
                    {
                        while (res.Read())
                        {
                            var user = new User()
                            {
                                userID = res["UserID"].ToString(),
                                firstName = res["FirstName"].ToString(),
                                lastName = res["LastName"].ToString()
                            };
                            if (string.IsNullOrEmpty(filter))
                            {
                                list.Add(user);
                            }
                            else
                            {
                                foreach (string term in filter.ToLower().Split())
                                {
                                    if (user.userID.ToLower().Contains(term) || 
                                        user.firstName.ToLower().Contains(term) || 
                                        user.lastName.ToLower().Contains(term))
                                    {
                                        list.Add(user);
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
                conn.Close();
            }
            return list;
        }
        
        public static User GetUser(string userID)
        {
            if (userID.Any(c => !char.IsDigit(c)))
            {
                return null;
            }
            using (var conn = new SQLiteConnection(@"Data Source=" + dbFile))
            {
                User user;
                conn.Open();
                using (var cmd = conn.CreateCommand())
                {
                    cmd.CommandType = CommandType.Text;
                    cmd.CommandText = @"SELECT * FROM Users WHERE UserID = " + userID;
                    cmd.Prepare();
                    using (var res = cmd.ExecuteReader())
                    {
                        user = res.Read() ? new User()
                        {
                            userID = res["UserID"].ToString(),
                            firstName = res["FirstName"].ToString(),
                            lastName = res["LastName"].ToString()
                        } : null;
                    }
                }
                conn.Close();
                return user;
            }
        }

        public static bool CreateUser(string firstName, string lastName)
        {
            Func<string, bool> invalid = name =>
                name.Length == 0 || name.Any(c => !char.IsLetter(c));

            if (invalid(firstName) || invalid(lastName))
            {
                return false;
            }

            using (var conn = new SQLiteConnection(@"Data Source=" + dbFile))
            {
                conn.Open();
                using (var cmd = new SQLiteCommand(conn))
                {
                    cmd.CommandType = CommandType.Text;
                    cmd.CommandText =
                        @"INSERT INTO Users (FirstName, LastName) VALUES (@firstName, @lastName)";
                    cmd.Prepare();
                    cmd.Parameters.AddWithValue("@firstName", firstName);
                    cmd.Parameters.AddWithValue("@lastName", lastName);
                    cmd.ExecuteNonQuery();
                }
                conn.Close();
                return true;
            }                            
        }

        public static void UpdateUser(User user)
        {
            using (var conn = new SQLiteConnection(@"Data Source=" + dbFile))
            {
                conn.Open();
                using (var cmd = new SQLiteCommand(conn))
                {
                    cmd.CommandType = CommandType.Text;
                    cmd.CommandText =
                        @"UPDATE Users SET FirstName = @firstName, "  +
                        @"LastName = @lastName WHERE UserID = @userID";
                    cmd.Prepare();
                    cmd.Parameters.AddWithValue("@firstName", user.firstName);
                    cmd.Parameters.AddWithValue("@lastName", user.lastName);
                    cmd.Parameters.AddWithValue("@userID", user.userID);
                    cmd.ExecuteNonQuery();
                }
                conn.Close();
            }
        }

        public static void DeleteUser(User user)
        {
            using (var conn = new SQLiteConnection(@"Data Source=" + dbFile))
            {
                conn.Open();
                using (var cmd = new SQLiteCommand(conn))
                {
                    cmd.CommandType = CommandType.Text;
                    cmd.CommandText =
                        @"DELETE FROM Users WHERE UserID = @userID";
                    cmd.Prepare();
                    cmd.Parameters.AddWithValue("@userID", user.userID);
                    cmd.ExecuteNonQuery();
                }
                conn.Close();
            }
        }
    }
}
