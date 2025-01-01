from DBController.DBConnection import DBConnection

#此檔案寫法和SQL command有關係
#https://www.1keydata.com/tw/sql/sql.html
#https://learn.microsoft.com/zh-tw/dotnet/api/system.data.sqlclient.sqlcommand?view=dotnet-plat-ext-7.0


class StudentInfoTable:
    def insert_a_student(self, name):
        command = "INSERT INTO student_info (name) VALUES  ('{}');".format(name)     
        with DBConnection() as connection:
            cursor = connection.cursor()
            cursor.execute(command)
            connection.commit()

    def insert_score(self, name, data):
        student_id = self.select_a_student(name)
        for key in data.keys():
            command = "INSERT INTO subject_info VALUES  ('{}','{}','{}');".format(student_id[0],key,data.get(key))
            with DBConnection() as connection:
                cursor = connection.cursor()
                cursor.execute(command)
                connection.commit()


    def get_all_student(self):
        command = "SELECT * FROM student_info"
        
        with DBConnection() as connection:
            cursor = connection.cursor()
            cursor.execute(command)
            record_from_db = cursor.fetchall()
        return_list = []
        for name in [row['name'] for row in record_from_db]:
            id = self.select_a_student(name)
            return_list.append({"name":name,"scores":self.get_student_score(id[0])})
        return  return_list
    
    def get_student_score(self,std_id):
        command = "SELECT * FROM subject_info WHERE stu_id = '{}'".format(std_id)

        with DBConnection() as connection:
            cursor = connection.cursor()
            cursor.execute(command)
            record_from_db = cursor.fetchall()
        score_dict = {}
        for record in record_from_db :
            score_dict[record['subject']] = record['score']
        return score_dict

    def select_a_student(self, name):
        command = "SELECT * FROM student_info WHERE name='{}';".format(name)

        with DBConnection() as connection:
            cursor = connection.cursor()
            cursor.execute(command)
            record_from_db = cursor.fetchall()

        return [row['stu_id'] for row in record_from_db]

    def delete_a_student(self, stu_id):
        command = "DELETE FROM student_info WHERE stu_id='{}';".format(stu_id)
        command2 = "DELETE FROM subject_info WHERE stu_id='{}';".format(stu_id)
        with DBConnection() as connection:
            cursor = connection.cursor()
            cursor.execute(command)
            cursor.execute(command2)
            connection.commit()

    def delete_a_subject(self, stu_id,subject):
        command = "DELETE FROM subject_info WHERE stu_id='{}' AND subject='{}';".format(stu_id,subject)
        with DBConnection() as connection:
            cursor = connection.cursor()
            cursor.execute(command)
            connection.commit()

    def update_a_student(self, stu_id, name):
        command = "UPDATE student_info SET name='{}' WHERE stu_id='{}';".format(name, stu_id)

        with DBConnection() as connection:
            cursor = connection.cursor()
            cursor.execute(command)
            connection.commit()

    def update_subject(self, stu_id, subject,score):
        command = "UPDATE subject_info SET score='{}' WHERE stu_id='{}' AND subject='{}';".format(score, stu_id,subject)

        with DBConnection() as connection:
            cursor = connection.cursor()
            cursor.execute(command)
            connection.commit()
       