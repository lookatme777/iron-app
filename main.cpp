#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QSlider>
#include <QHBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QLabel>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Создаем основное окно
    QWidget windowIRONAPP;
    windowIRONAPP.setWindowTitle("IRONAPP");

    // Создаем сцену и представление
    QGraphicsScene scene;
    QGraphicsView view(&scene);

    // Создаем изображение
    QPixmap ironman("/home/killreal/Documents/qtproject/IronApp/ironman.png");
    QPixmap apple("/home/killreal/Documents/qtproject/IronApp/apple.png");
    QPixmap scaledapple = apple.scaled(100, 100);
    QGraphicsPixmapItem *iron = new QGraphicsPixmapItem(ironman);
    QGraphicsPixmapItem *app = new QGraphicsPixmapItem(scaledapple);
    iron->setPos(200, 20);  //начальная позиция изображения
    app->setPos(0,120);     //начальная позиция изображения


    scene.addItem(iron);    //добавили изображение в сцену
    scene.addItem(app);     //добавили изображение в сцену

    // Создаём кнопку
    QPushButton *exit = new QPushButton("EXIT");
    QObject::connect(exit, SIGNAL(clicked()), &a, SLOT(quit()));


    // Создаем ползунок
    QSlider ironSLIDER(Qt::Horizontal);
    QSlider appleSLIDER(Qt::Horizontal);


    ironSLIDER.setRange(0, 200);   //направление ползунка
    ironSLIDER.setValue(400);      //начальное значение ползунка
    appleSLIDER.setValue(0);

    // Метка для определиня соприкоснавения изображений
    QLabel *collisionlabel = new QLabel("IRON & APPLE");

    // Связываем изменение значения ползунка с перемещением изображения
    QObject::connect(&appleSLIDER, &QSlider::valueChanged, [&](int value){
        app->setX(value);

        if(iron->collidesWithItem(app)){
            collisionlabel->setText("IRON MAN EATS APPLE");
        } else{
            collisionlabel->setText("IRON & APPLE");
        }



    });
    QObject::connect(&ironSLIDER, &QSlider::valueChanged, [&](int value){
        iron->setX(value);

        if(iron->collidesWithItem(app)){
            collisionlabel->setText("IRON MAN EATS APPLE");
        } else{
            collisionlabel->setText("IRON & APPLE");
        }
    });


    // Размещаем элементы на форме
    QVBoxLayout layout(&windowIRONAPP);
    layout.addWidget(&view);
    layout.addWidget(&ironSLIDER);
    layout.addWidget(&appleSLIDER);
    layout.addWidget(exit);
    layout.addWidget(collisionlabel);



    // Отображаем окно
    windowIRONAPP.show();

    return a.exec();
}
