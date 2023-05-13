#include "formatdialog.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QColorDialog>
#include <QTextBlockFormat>

FormatDialog::FormatDialog(QWidget *parent)
        : QDialog(parent)
{
    setWindowTitle(tr("Форматирование текста"));

    // Создаем виджеты для выбора шрифта и размера
    m_fontComboBox = new QFontComboBox(this);

    m_fontSizeSpinBox = new QSpinBox(this);
    m_fontSizeSpinBox->setRange(6, 72);

    // Создаем метки для виджетов
    QLabel *fontLabel = new QLabel(tr("Шрифт:"), this);
    QLabel *fontSizeLabel = new QLabel(tr("Размер:"), this);

    // Создаем горизонтальный лэйаут для виджетов и меток
    QHBoxLayout *fontLayout = new QHBoxLayout();
    fontLayout->addWidget(fontLabel);
    fontLayout->addWidget(m_fontComboBox);
    fontLayout->addWidget(fontSizeLabel);
    fontLayout->addWidget(m_fontSizeSpinBox);

    // Создаем кнопку для выбора цвета текста и лейбл для отображения текущего цвета
    QPushButton *colorButton = new QPushButton(tr("Цвет"), this);
    m_colorLabel = new QLabel(this);

    // Создаем виджеты для выбора выравнивания текста
    QPushButton *leftButton = new QPushButton(tr("Лево"), this);
    leftButton->setCheckable(true);
    leftButton->setChecked(true);

    QPushButton *centerButton = new QPushButton(tr("Центр"), this);
    centerButton->setCheckable(true);

    QPushButton *rightButton = new QPushButton(tr("Право"), this);
    rightButton->setCheckable(true);

    // Создаем группу кнопок для выравнивания текста
    m_alignmentGroup = new QButtonGroup(this);
    m_alignmentGroup->addButton(leftButton, Qt::AlignLeft);
    m_alignmentGroup->addButton(centerButton, Qt::AlignCenter);
    m_alignmentGroup->addButton(rightButton, Qt::AlignRight);

    // Создаем виджеты для выбора стиля текста
    m_boldCheckBox = new QCheckBox(tr("Жирный"), this);
    m_italicCheckBox = new QCheckBox(tr("Курсив"), this);
    m_underlineCheckBox = new QCheckBox(tr("Подчеркнутый"), this);

    // Создаем горизонтальный лэйаут для виджетов стиля текста
    QHBoxLayout *styleLayout = new QHBoxLayout();
    styleLayout->addWidget(m_boldCheckBox);
    styleLayout->addWidget(m_italicCheckBox);
    styleLayout->addWidget(m_underlineCheckBox);

    // Создаем горизонтальный лэйаут для кнопок выравнивания текста
    QHBoxLayout *alignmentLayout = new QHBoxLayout();
    alignmentLayout->addWidget(leftButton);
    alignmentLayout->addWidget(centerButton);
    alignmentLayout->addWidget(rightButton);

    // Создаем кнопки OK и Cancel
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    // Создаем вертикальный лэйаут для всего диалога
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(fontLayout);
    mainLayout->addWidget(colorButton);
    mainLayout->addWidget(m_colorLabel);
    mainLayout->addLayout(styleLayout);
    mainLayout->addLayout(alignmentLayout);
    mainLayout->addWidget(buttonBox);

    // Соединяем сигналы и слоты
    connect(buttonBox, &QDialogButtonBox::accepted, this, &FormatDialog::applyFormat);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &FormatDialog::reject);

    connect(colorButton, &QPushButton::clicked, this, &FormatDialog::chooseColor);

    connect(m_alignmentGroup, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked), this,
        [this](QAbstractButton *button) {
        m_alignment = static_cast<Qt::Alignment>(m_alignmentGroup->id(button)); // Сохраняем выбранное выравнивание в переменной-члене класса
            });
}

void FormatDialog::initDialog(QTextEdit *textEdit)
{
    m_textEdit = textEdit;
    // Устанавливаем текущие значение шрифта и размера
    m_fontComboBox->setCurrentFont(m_textEdit->currentFont());
    m_fontSizeSpinBox->setValue(m_textEdit->currentFont().pointSize());

    QTextCharFormat format = textEdit->currentCharFormat();

    // Устанавливаем текущие значение цвета, а также устанавливаем его в фоновый цвет для QLabel
    m_color = format.foreground().color();
    m_colorLabel->setStyleSheet(QString("background-color: %1").arg(m_color.name()));

    // Определяем текущий курсив и устанавливаем нужные галочки (жирный, курсив, подчеркнутый)
    bool isItalic = format.fontItalic();

    int fontWeight = format.fontWeight();
    bool isBold = (fontWeight == QFont::Bold);

    bool isUnderline = format.fontUnderline();

    if(isItalic)
    {
        m_italicCheckBox->setChecked(true);
    }
    if(isBold)
    {
        m_boldCheckBox->setChecked(true);
    }
    if(isUnderline)
    {
        m_underlineCheckBox->setChecked(true);
    }

    if(!isItalic && !isBold && !isUnderline)
    {
        m_italicCheckBox->setChecked(false);
        m_boldCheckBox->setChecked(false);
        m_underlineCheckBox->setChecked(false);
    }

    // Определяем текущее выравнивание текста и нажимаем нужные кнопки (лево, центр, право)
    m_alignment=m_textEdit->alignment();
    switch (m_alignment)
    {
    case 0:
        m_alignmentGroup->button(0)->setChecked(true);
        break;
    case 1:
        m_alignmentGroup->button(1)->setChecked(true);
        break;
    case 2:
        m_alignmentGroup->button(2)->setChecked(true);
        break;
    default:
        break;
    }
}

void FormatDialog::applyFormat()
{
    // Применяем выбранный шрифт и размер к выделенному тексту
    QTextCursor cursor = m_textEdit->textCursor();
    QTextCharFormat format;
    format.setFont(m_fontComboBox->currentFont());
    format.setFontPointSize(m_fontSizeSpinBox->value());
    format.setForeground(m_color); // Применяем выбранный цвет текста
    format.setFontWeight(m_boldCheckBox->isChecked() ? QFont::Bold : QFont::Normal); // Применяем выбранный стиль курсива текста
    format.setFontItalic(m_italicCheckBox->isChecked());
    format.setFontUnderline(m_underlineCheckBox->isChecked());
    cursor.mergeCharFormat(format);

    // Применяем выбранное выравнивание к абзацу текста
    QTextBlockFormat blockFormat;
    blockFormat.setAlignment(m_alignment);
    cursor.mergeBlockFormat(blockFormat);

    accept();
}

void FormatDialog::chooseColor()
{
    // Вызываем диалог выбора цвета и сохраняем выбранный цвет в переменной-члене класса
    m_color = QColorDialog::getColor(m_textEdit->textColor(), this);
    // Устанавливаем выбранный цвет в фоновый цвет для QLabel
    m_colorLabel->setStyleSheet(QString("background-color: %1").arg(m_color.name()));
}
