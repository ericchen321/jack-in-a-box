import requests
import boto3

def sendPOST(url, data):
    print("Sending payload via HTTP POST to: " + url)
    response = requests.request("POST", "http://d1umgoqwy5q61i.cloudfront.net", data=data, headers={'Content-type': 'application/json', 'Content-length':bytes(len(data)), 'Connection': 'close'})
    if "200" in str(response):
        print("POST was successful. Response: \n\n" + response.text)
    else:
        print(response.text)

def main():
    stackName = "cpen-391-stack"
    cloudformation = boto3.client("cloudformation")
    stack = cloudformation.describe_stacks(StackName=stackName)['Stacks'][0]

    url = list(filter(lambda x: x['OutputKey'] == "APIInvokeURL", stack['Outputs']))[0]['OutputValue']
    data = '{"username": "noob", "game_result": "t", "phone_number": "+17788469337"}'
    data1 = '{"username": "john", "game_result": "w", "phone_number": "+17788469337"}'
    data2 = '{"username": "carrot", "game_result": "l", "phone_number": "+17788469337"}'

    sendPOST(url, data)
   # sendPOST(url, data1)
   # sendPOST(url, data2)


if __name__ == "__main__":
    main()
