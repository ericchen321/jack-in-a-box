import requests
import boto3

def sendPOST(url, data):
    print("Sending payload via HTTP POST to: " + url)
    response = requests.request("POST", url, data=data)
    if "200" in str(response):
        print("POST was successful. Response: \n\n" + response.text)

def main():
    stackName = "cpen-391-stack"
    cloudformation = boto3.client("cloudformation")
    stack = cloudformation.describe_stacks(StackName=stackName)['Stacks'][0]

    url = list(filter(lambda x: x['OutputKey'] == "APIInvokeURL", stack['Outputs']))[0]['OutputValue']
    data = "I am the payload"

    sendPOST(url, data)


if __name__ == "__main__":
    main()