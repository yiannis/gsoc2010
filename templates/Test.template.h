#ifndef OY_TEST_H
#define OY_TEST_H

#include <QtTest>
#include <QObject>

class oyTest: public QObject
{
  Q_OBJECT

    private slots:
{% for class in classes %}
      void {{ class.name }}_generic_methods();
      void {{ class.privName }}_generic_methods();
{% endfor %}
};

#endif //OY_TEST_H