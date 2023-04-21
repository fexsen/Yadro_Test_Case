#include <ns3/core-module.h>
#include <ns3/network-module.h>
#include <ns3/mobility-module.h>
#include <ns3/lte-module.h>

using namespace ns3;

int main(int argc, char *argv[])
{

    Ptr<LteHelper> lteHelper = CreateObject<LteHelper>();

    // Создаем объект-узел базовой станции (eNodeB)
    NodeContainer enbNodes;
    enbNodes.Create(1);
    // Создаем два объекта-узла абонента
    NodeContainer ueNodes;
    ueNodes.Create(2);

    // Устанавливаем все узлы на координаты (0, 0, 0)
    MobilityHelper mobility;
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(enbNodes);
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(ueNodes);

    // Создаем устройство eNB
    NetDeviceContainer enbDevs;
    enbDevs = lteHelper->InstallEnbDevice(enbNodes);

    // Создаем устройства Ue
    NetDeviceContainer ueDevs;
    ueDevs = lteHelper->InstallUeDevice(ueNodes);

    // Устанавливаем соединение между объектом базовой станции и абонентами 
    lteHelper->Attach(ueDevs, enbDevs.Get(0));

    // Активируем передачу трафика
    enum EpsBearer::Qci q = EpsBearer::GBR_CONV_VOICE;
    EpsBearer bearer(q);
    lteHelper->ActivateDataRadioBearer(ueDevs, bearer);

    // Настраиваем планировщик пакетов
    lteHelper->SetSchedulerType ("ns3::PfFfMacScheduler");

    // Настраиваем вывод ключевых характеристик с RLC и MAC уровня, информация о Dl и Ul характеристиках по умолчанию хранится в файлах Dl(MAC/RLC)Stats.txt и Ul(MAC/RLC)Stats.txt 
    lteHelper->EnableRlcTraces();
    lteHelper->EnableMacTraces();

    // Пакеты в данном случае передаются в обе стороны бесконечно
    // Запускаем сценарий
    Simulator::Run();
    Simulator::Destroy();
    return 0;

}