# import flask
from flask import Flask, request,render_template
import utils.response as response
import utils.database as db

# create server
server = Flask(__name__)

@server.route("/welcome")
def welcome():
    return response.create_response("Welcome to IoT Application");

@server.route("/slot", methods = {'GET', 'PUT'})
def slot_methods():
    if (request.method == 'GET'):
        # to get data from database form a query
        query = f"select * from slot_status;"
        #query = f"select slot_status from slot_status where slot_no=1;"

        # execute query to get all slots from database
        slots = db.execute_select_query(query)
        
        print(f"\nSlots : {slots}\n")

        # return slots into response
        return render_template("table.html", message=slots)
        #return response.create_response(slots)
    
    elif(request.method == 'PUT'):
        slot_no = request.get_json().get('slot_no')
        slot_status = request.get_json().get('slot_status')

        # insert data into database
        query = f"update slot_status set time=CURRENT_TIMESTAMP , slot_status = \"{slot_status}\" where slot_no = \"{slot_no}\";"
        db.execute_query(query)
        print(f"slot status = {slot_status}")   
        return response.create_response1("slot_status updated successfully")

    elif(request.method == 'DELETE'):
        pass


# run server
server.run(host="0.0.0.0", port=5000, debug=True)