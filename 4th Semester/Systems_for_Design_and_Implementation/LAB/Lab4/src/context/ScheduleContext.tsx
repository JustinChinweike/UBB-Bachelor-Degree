
import React, { createContext, useState, useContext, ReactNode, useEffect } from "react";
import { Schedule } from "../types/schedule";
import { initialSchedules } from "../data/mockData";
import { toast } from "@/hooks/use-toast";

interface ScheduleContextType {
  schedules: Schedule[];
  addSchedule: (schedule: Omit<Schedule, "id">) => void;
  updateSchedule: (id: string, updatedSchedule: Omit<Schedule, "id">) => void;
  deleteSchedule: (id: string) => void;
  getScheduleById: (id: string) => Schedule | undefined;
  filteredSchedules: Schedule[];
  setFilterCriteria: React.Dispatch<React.SetStateAction<{
    doctorName: string;
    patientName: string;
    department: string;
  }>>;
}

const LOCAL_STORAGE_KEY = "hospital_schedules";

const ScheduleContext = createContext<ScheduleContextType | undefined>(undefined);

export const ScheduleProvider: React.FC<{ children: ReactNode }> = ({ children }) => {
  // Initialize state from localStorage or fall back to initialSchedules
  const [schedules, setSchedules] = useState<Schedule[]>(() => {
    if (typeof window !== 'undefined') {
      const savedSchedules = localStorage.getItem(LOCAL_STORAGE_KEY);
      return savedSchedules ? JSON.parse(savedSchedules) : initialSchedules;
    }
    return initialSchedules;
  });
  
  const [filterCriteria, setFilterCriteria] = useState({
    doctorName: "",
    patientName: "",
    department: "",
  });

  // Save to localStorage whenever schedules change
  useEffect(() => {
    console.log("Saving schedules to localStorage:", schedules);
    localStorage.setItem(LOCAL_STORAGE_KEY, JSON.stringify(schedules));
  }, [schedules]);

  // Filter schedules based on criteria
  const filteredSchedules = schedules.filter(schedule => {
    return (
      (filterCriteria.doctorName === "" || 
        schedule.doctorName.toLowerCase().includes(filterCriteria.doctorName.toLowerCase())) &&
      (filterCriteria.patientName === "" || 
        schedule.patientName.toLowerCase().includes(filterCriteria.patientName.toLowerCase())) &&
      (filterCriteria.department === "" || filterCriteria.department === "all" || 
        schedule.department === filterCriteria.department)
    );
  });

  // Add a new schedule
  const addSchedule = (schedule: Omit<Schedule, "id">) => {
    const newSchedule = {
      ...schedule,
      id: Date.now().toString(), // Generate a unique ID
    };
    
    setSchedules(prevSchedules => {
      console.log("Adding new schedule:", newSchedule);
      return [...prevSchedules, newSchedule];
    });
    
    toast({
      title: "Schedule Added",
      description: "The appointment has been successfully scheduled",
    });
  };

  // // Update an existing schedule
  // const updateSchedule = (id: string, updatedSchedule: Omit<Schedule, "id">) => {
  //   setSchedules(prevSchedules => {
  //     console.log("Updating schedule:", id, updatedSchedule);
  //     return prevSchedules.map(schedule => 
  //       schedule.id === id 
  //         ? { ...updatedSchedule, id } 
  //         : schedule
  //     );
  //   });


  //   toast({
  //     title: "Schedule Updated",
  //     description: "The appointment has been successfully updated",
  //   });
  // };

  const updateSchedule = (id: string, updatedSchedule: Omit<Schedule, "id">) => {
    setSchedules(prevSchedules => {
      const newSchedules = prevSchedules.map(schedule => 
        schedule.id === id 
          ? { ...schedule, ...updatedSchedule } //  Fix: Merge old data correctly!
          : schedule
      );
  
      // Save updated schedules to localStorage
      localStorage.setItem("hospital_schedules", JSON.stringify(newSchedules));
  
      return newSchedules;
    });
  
    toast({
      title: "Schedule Updated",
      description: "The appointment has been successfully updated",
    });
  };
  





  // Delete a schedule
  const deleteSchedule = (id: string) => {
    setSchedules(prevSchedules => {
      console.log("Deleting schedule:", id);
      return prevSchedules.filter(schedule => schedule.id !== id);
    });
    
    toast({
      title: "Schedule Deleted",
      description: "The appointment has been removed from the system",
    });
  };

  // Get a schedule by ID
  const getScheduleById = (id: string) => {
    return schedules.find(schedule => schedule.id === id);
  };

  return (
    <ScheduleContext.Provider value={{ 
      schedules, 
      addSchedule, 
      updateSchedule, 
      deleteSchedule, 
      getScheduleById,
      filteredSchedules,
      setFilterCriteria
    }}>
      {children}
    </ScheduleContext.Provider>
  );
};

export const useSchedule = () => {
  const context = useContext(ScheduleContext);
  if (context === undefined) {
    throw new Error("useSchedule must be used within a ScheduleProvider");
  }
  return context;
};
