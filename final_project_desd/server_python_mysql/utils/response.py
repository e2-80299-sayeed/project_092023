from flask import jsonify

def create_response(data, error=None):
    # create empty dictionary
    d = dict()

    if(error == None):
        d = {
            "status":"success"  ,
            "data 4": data[1][1],
            "data 3": data[1][0],
            "data 2": data[0][1],
            "data 1":data[0][0]
        }
    else:
        d = {
            "status":"failure"
        }

    return jsonify(d)

def create_response1(data, error=None):
    # create empty dictionary
    d = dict()

    if(error == None):
        d = {
            "status":"success"  ,
            "data 4": data
        }
    else:
        d = {
            "status":"failure"
        }

    return jsonify(d)