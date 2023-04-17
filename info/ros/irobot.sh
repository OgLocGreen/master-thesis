#!/bin/bash

echo Lanzando nodos necesarios para la inspeccion y reparacion

read -p "ENTER para lanzar los servidores de la inspeccion"
gnome-terminal -e "bash -c 'source realsense_ws/devel/setup.bash && roslaunch inspection_realsense launch_inspection_actionservers.launch'"

read -p "ENTER para lanzar los servidores de la reparacion"
gnome-terminal -e "bash -c 'source nav_insp_ws/devel/setup.bash && roslaunch action_server_package launch_all_actionservers.launch'"

read -p "ENTER para lanzar FlexBE"
gnome-terminal -e "bash -c 'source nav_insp_ws/devel/setup.bash && roslaunch flexbe_app flexbe_full.launch'"

echo Entorno lanzado
