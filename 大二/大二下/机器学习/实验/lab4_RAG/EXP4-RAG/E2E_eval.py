from NaiveRAG import NaiveRAG

import json
from llm_client import run_llm


def rewrite_query(question):
    #TODO: 修改prompt，思考怎么样LLM更容易正确回答
    # prompt = f"Rewrite the following question to make it more specific and clear: {question}"
    prompt = f"You are a helpful assistant. Rewrite the question to make it more specific, include any implicit entities or time spans: Original question{question}"
    response = run_llm(prompt, 0.0, 4096, "sk-52152be10de24ba091f660dca2f9115f")
    return response

def main():
    rag = NaiveRAG(
        embedding_dim=1024,  # Set according to your model's output dimension
        work_dir="./work_dir",
        model="bge-large"    # The model name used in your local Ollama
    )
    total = 0
    correct = 0
    retrieved = 0
    relevant = 0
    with open("musique_dev.jsonl", "r", encoding="utf-8") as f:
        for i, line in enumerate(f):
            if i >= 100:
                break
            data = json.loads(line)
            question = data["question"]
            #TODO: 重写query能够得到与问题更相关的语料
            question = rewrite_query(question)
            gold_answer = data["answer"]
            answer_aliases = data.get("answer_aliases", [])
            # context = data["context"]  # Not used in this evaluation
            prompt = rag.generate_prompt(question, 10)
            #TODO：这里加上自己的key
            response = run_llm(prompt, 0.0, 4096, "sk-52152be10de24ba091f660dca2f9115f")
            print(f"Q: {question}")
            print(f"Gold: {gold_answer}")
            print(f"Pred: {response}")
            print("="*20)
            total += 1

            # Simple string matching for answer checking (can be improved)
            # Collect all possible correct answers including aliases
            if isinstance(gold_answer, list):
                all_gold_answers = list(gold_answer)  # Create a copy
            else:
                all_gold_answers = [gold_answer]
            relevant += len(gold_answer.split(','))

            all_gold_answers.extend(answer_aliases)
            #relevant += len(all_gold_answers)
            
            # For recall: count all gold answers
            

            gold_set = {str(a).strip().lower() for a in all_gold_answers}

            # Extract answer from response that is wrapped in {}
            import re
            answers = re.findall(r'\{([^}]*)\}', response)
            if answers:
                # Split multiple answers by comma and clean them
                response_answers = [ans.strip().lower() for ans in answers[0].split(',')]
                response_set = set(response_answers)
                # print(f"Response: {response_set}")
            else:
                response_set = set()
                # print(f"Response: {response_set}")

            
            # For precision: count all predicted answers
            retrieved += len(response_set)
            # Count correct matches (intersection)
            correct += len(gold_set & response_set)
            print(f"Gold: {gold_set}")
            print(f"Response: {response_set}")
            print(f"Correct: {correct}")
            print(f"Retrieved: {retrieved}")
            print(f"Relevant: {relevant}")
            print("="*20)

    precision = correct / retrieved if retrieved > 0 else 0.0
    recall = correct / relevant if relevant > 0 else 0.0
    f1 = 2 * precision * recall / (precision + recall) if (precision + recall) > 0 else 0.0
    print(f"Total: {total}")
    print(f"Correct: {correct}")
    print(f"Precision: {precision:.4f}")
    print(f"Recall: {recall:.4f}")
    print(f"F1: {f1:.4f}")
    
if __name__ == "__main__":
    main()






