from DBConnection import DBConnection


class StudentInfoTable:
    def insert_a_name(self, name):
        command = "INSERT INTO student_info (name) VALUES  ('{}');".format(name)
            
        with DBConnection() as connection:
            cursor = connection.cursor()
            cursor.execute(command)
            connection.commit()

    def insert_a_subject(self, stu_id, subject ,score):
        command = "INSERT INTO subject_info VALUES  ('{}','{}','{}');".format(stu_id ,subject ,score)
            
        with DBConnection() as connection:
            cursor = connection.cursor()
            cursor.execute(command)
            connection.commit()

    def select_a_student(self, name):
        command = "SELECT * FROM student_info WHERE name='{}';".format(name)

        with DBConnection() as connection:
            cursor = connection.cursor()
            cursor.execute(command)
            record_from_db = cursor.fetchall()

        return [row['stu_id'] for row in record_from_db]
    
    def select_all_student(self):
        command = "SELECT * FROM student_info;"

        with DBConnection() as connection:
            cursor = connection.cursor()
            cursor.execute(command)
            record_from_db = cursor.fetchall()

        return record_from_db
    
    def select_a_subject(self, stu_id):
        command = "SELECT * FROM subject_info WHERE stu_id='{}';".format(stu_id)

        with DBConnection() as connection:
            cursor = connection.cursor()
            cursor.execute(command)
            record_from_db = cursor.fetchall()

        return record_from_db

    def delete_a_student(self, stu_id):
        command = "DELETE FROM student_info WHERE stu_id='{}';".format(stu_id)

        with DBConnection() as connection:
            cursor = connection.cursor()
            cursor.execute(command)
            connection.commit()

    def delete_a_subject(self, stu_id):
        command = "DELETE FROM subject_info WHERE stu_id='{}';".format(stu_id)

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
    
    def update_a_subject(self, stu_id, subject ,score):
        command = "UPDATE subject_info SET score='{}' WHERE stu_id='{}' AND subject='{}';".format(score, stu_id, subject)

        with DBConnection() as connection:
            cursor = connection.cursor()
            cursor.execute(command)
            connection.commit()