# Hospital Scheduling Web Application

## Project Overview
This full-stack web application enables hospital staff to manage appointments (schedules) efficiently. The system supports creating, viewing, updating, and deleting appointment records, with filtering and sorting capabilities. It includes advanced features such as offline access (operations queue with local storage), real-time updates via WebSockets, dynamic charts for data visualization, and support for uploading attached files. The project is structured into **Bronze**, **Silver**, and **Gold** challenge tiers, each adding progressively advanced functionality.

---

## 🔍 Features Implemented

### 🥉 Bronze Tier (Grade 5)
- [x] **CRUD REST API** (Express + TypeScript)  
  - `POST /schedules`  
  - `GET /schedules` (with filtering, sorting, pagination)  
  - `GET /schedules/:id`  
  - `PATCH /schedules/:id`  
  - `DELETE /schedules/:id`
- [x] **Filtering & Sorting**  
  - Query parameters: `doctorName`, `patientName`, `department`, `dateTime`, `sortBy`, `sortOrder`
- [x] **Server-Side Validation** (Zod)  
  - Validates `POST` and `PATCH` payloads; returns **400** on error
- [x] **Unit Tests** (Jest)  
  - Controller tests for all endpoints  
  - Mocked Express `Request`/`Response` and Socket.IO events  
  - Run with `npm test` in **backend/**

### 🥈 Silver Tier (Grade 7)
- [x] **Offline Support**  
  - Detects browser/network/server status  
  - Displays an offline indicator  
  - Queues CRUD operations in `localStorage` when offline; syncs on reconnect
- [x] **Endless Scrolling & Pagination**  
  - Frontend list fetches additional pages as user scrolls  
  - Backend supports `?page=` and `?limit=` query parameters

### 🥇 Gold Tier (Grade 10)
- [x] **Real-Time Updates** (Socket.IO)  
  - Backend auto-generates a new appointment every 10 s  
  - Emits `new_schedule`, `updated_schedule`, `deleted_schedule` events  
  - Frontend updates UI live without refresh
- [x] **Dynamic Charts** (Recharts)  
  - Bar/Pie charts for appointments by department, doctor, date  
  - Charts update in real time
- [x] **File Upload/Download**  
  - Uses Multer on the backend (max 5 MB)  
  - Stores uploads in `uploads/` and serves them via `/uploads/*`  
  - Frontend can attach/view files per appointment

---

## 🚀 Technology Stack

- **Backend**  
  - Node.js, Express.js (v5), TypeScript  
  - Socket.IO (real-time)  
  - Zod (validation)  
  - Multer (file uploads)  
  - Jest & ts-jest (unit testing)  
  - UUID, CORS, Nodemon

- **Frontend**  
  - Vite, React 18, TypeScript  
  - Tailwind CSS, shadcn/UI, Radix UI  
  - React Router, React Query  
  - Recharts (charts)  
  - Axios (HTTP client)

---

## 📁 Folder Structure
HospitalSchedulingApp/ ├── backend/ # Express/TypeScript server │ ├── src/ │ │ ├── controllers/ # scheduleController.ts │ │ ├── models/ # scheduleModel.ts (in-memory + Zod schema) │ │ ├── routes/ # scheduleRoutes.ts, downloadRoutes.ts │ │ ├── socket.ts # initSocket, io export │ │ └── index.ts # server entry point │ ├── uploads/ # stored uploaded files │ ├── package.json │ └── tsconfig.json └── frontend/ # Vite/React client ├── src/ │ ├── components/ # UI components (forms, charts, status, etc.) │ ├── context/ # ScheduleContext, OfflineContext │ ├── hooks/ # useSchedule, useOffline, useToast │ ├── pages/ # Index, Add/Edit/List pages │ ├── utils/ # formValidation, apiClient │ └── main.tsx # app entry point ├── package.json ├── vite.config.ts # dev server on port 8080 └── tailwind.config.ts



---

## ⚙️ Installation & Running Instructions

1. **Clone the repository**  
   ```bash
   git clone <YOUR_GITHUB_URL>
   cd HospitalSchedulingApp

2. **Backend Setup**
   ```bash
   cd backend
   npm install
   npm run dev
  # Server will listen on http://localhost:5000
  
3. **Frontend Setup**
   ```bash
   cd ../frontend
   npm install
   npm run dev
# App will open at http://localhost:8080
   

4. Access the Application
Open your browser at http://localhost:8080, which communicates with the backend at http://localhost:5000.

## 🧪 Testing Instructions
# Backend Unit Tests
```bash
cd backend
npm test
````
#All Jest tests (in src/controllers/__tests__/scheduleController.test.ts) should pass.

# Frontend
Manual testing by interacting with the UI, including offline mode, real-time updates, charts, and file uploads.





