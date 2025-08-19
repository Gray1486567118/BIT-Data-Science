from openai import OpenAI
import time
import json

def run_llm(prompt, temperature, max_tokens, openai_api_keys, engine="qwen-plus-2025-01-25"):
    base_url_ = "https://dashscope.aliyuncs.com/compatible-mode/v1"
    if(engine.split('-')[0]=='gpt'):
        base_url_  = "https://api.openai.com/v1"
    elif(engine.split('-')[0]=='moonshot'):
        base_url_ = "https://api.moonshot.cn/v1"
    elif(engine.split('-')[0]=='qwen'):
        base_url_ = "https://dashscope.aliyuncs.com/compatible-mode/v1"
    client =  OpenAI(
        api_key=openai_api_keys,
        base_url= base_url_
    )
    if "llama" in engine.lower():
        openai.api_key = "EMPTY"
        openai.api_base = "http://localhost:8000/v1"  # your local llama server port
        #engine = openai.Model.list()["data"][0]["id"]
        client = OpenAI(
            base_url = 'http://localhost:11434/v1',
            api_key='ollama', # required, but unused
        )

    messages = [{"role":"system","content":"You are an AI assistant that helps people find information."}]
    message_prompt = {"role":"user","content":prompt}
    messages.append(message_prompt)
    f = 0
    while(f == 0):
        try:
            #response = openai.ChatCompletion.create(
            response = client.chat.completions.create(
                    model=engine,
                    messages = messages,
                    temperature=temperature,
                    max_tokens=max_tokens,
                    frequency_penalty=0,
                    presence_penalty=0)
            #print(response)
            result = json.loads(response.model_dump_json())["choices"][0]['message']['content']
            f = 1
        except:
            print("openai error, retry")
            time.sleep(2)
    return result