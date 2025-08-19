import json
from typing import List
from pathlib import Path

def process_jsonl_file(input_file: str, output_file: str, limit: int = 100):
    paragraphs: List[str] = []
    
    # Read JSONL file
    with open(input_file, 'r', encoding='utf-8') as f:
        seen_paragraphs = set()
        for i, line in enumerate(f):
            if i >= limit:
                break
            
            data = json.loads(line)
            # Extract and concatenate paragraph texts
            if "paragraphs" in data:
                for para in data["paragraphs"]:
                    if "paragraph_text" in para:
                        paragraph_text = para["paragraph_text"]
                        if paragraph_text not in seen_paragraphs:
                            paragraphs.append(paragraph_text)
                            seen_paragraphs.add(paragraph_text)
    
    # Write concatenated paragraphs to output file
    with open(output_file, 'w', encoding='utf-8') as f:
        for para in paragraphs:
            f.write(para + "\n")  # Add double newline for readability

if __name__ == "__main__":
    input_file = "musique_dev.jsonl"
    output_file = "concatenated_paragraphs.txt"
    process_jsonl_file(input_file, output_file)
    print(f"Processed paragraphs have been saved to {output_file}")

