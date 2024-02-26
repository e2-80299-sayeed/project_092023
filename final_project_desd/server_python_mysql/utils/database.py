import utils.connection as conn

def execute_query(query):
    connection = conn.get_connection()

    cursor = connection.cursor()
    cursor.execute(query)
    connection.commit()

    cursor.close()
    connection.close()

def execute_select_query(query):
    connection = conn.get_connection()

    cursor = connection.cursor()
    cursor.execute(query)
    data = cursor.fetchall()  # list of tuples

    cursor.close()
    connection.close()

    return data