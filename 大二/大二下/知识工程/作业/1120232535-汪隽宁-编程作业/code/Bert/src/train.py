import torch
from ruamel.yaml import YAML
from transformers import TrainingArguments, Trainer, AutoTokenizer
from dataset import TCMDataset
from model import BertForTCM
from utils import set_seed, compute_metrics


def main():
    # 读取配置
    cfg = YAML(typ='safe').load(open('config.yaml', encoding='utf-8'))
    set_seed(cfg['seed'])

    # 加载数据集
    train_ds = TCMDataset(
        path=cfg['data']['train_path'],
        tokenizer_name=cfg['model_name'],
        max_length=cfg['max_length'],
        mode='train'
    )
    val_ds = TCMDataset(
        path=cfg['data']['val_path'],
        tokenizer_name=cfg['model_name'],
        max_length=cfg['max_length'],
        mode='train'
    )

    # 加载模型
    model = BertForTCM.from_pretrained(cfg['model_name'])


    # 训练参数
    training_args = TrainingArguments(
        output_dir=cfg['output_dir'],
        num_train_epochs=cfg['num_epochs'],
        per_device_train_batch_size=cfg['train_batch_size'],
        per_device_eval_batch_size=cfg['eval_batch_size'],
        learning_rate=cfg['lr'],
        logging_dir=cfg['logging_dir'],
        do_eval=True,
        save_total_limit=3, 
        logging_steps=50,    
    )

    # 构造 Trainer
    trainer = Trainer(
        model=model,
        args=training_args,
        train_dataset=train_ds,
        eval_dataset=val_ds,
        compute_metrics=compute_metrics
    )

    # 启动训练
    trainer.train()

    # 保存模型
    trainer.save_model(cfg['output_dir'])


if __name__ == '__main__':
    main()